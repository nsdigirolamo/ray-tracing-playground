#include <list>
#include <memory>

#include "camera.hpp"
#include "intersectables/intersectable.hpp"
#include "intersectables/plane.hpp"
#include "lib/doctest/doctest.hpp"
#include "materials/diffuse.hpp"
#include "materials/metallic.hpp"
#include "primitives/matrix.cuh"
#include "primitives/vector.hpp"
#include "test/test_utils.hpp"

Point expected_location {{0, 0, 0}};
int expected_image_height = 1080;
int expected_image_width = 1920;
double expected_horizontal_fov = 90;
Point expected_looking_at {{0, 0, 1}};

Camera actual_camera {
    expected_location,
    expected_image_height,
    expected_image_width,
    expected_horizontal_fov,
    expected_looking_at
};

double expected_focal_distance = 1;
double expected_focal_radius = 0;
Vector<3> expected_view_direction {{0, 0, 1}};
Vector<3> expected_up_direction {{0, 1, 0}};
Vector<3> expected_view_horizontal {{-1, 0, 0}};
Vector<3> expected_view_vertical {{0, 1, 0}};
double expected_view_width = 2.0;
double expected_pixel_width = expected_view_width / expected_image_width;
double expected_view_height = expected_view_width * ((double)(expected_image_height) / (double)(expected_image_width));
double expected_pixel_height = expected_view_height / expected_image_height;
double expected_vertical_fov = 58.715507;

TEST_SUITE ("Camera Construction Tests") {

    TEST_CASE ("Camera Construction") {

        SUBCASE ("Location") {
            CHECK_VECTOR(expected_location, actual_camera.getLocation());
        }

        SUBCASE ("Image Dimensions") {
            CHECK(expected_image_height == actual_camera.getImageHeight());
            CHECK(expected_image_width == actual_camera.getImageWidth());
        }

        SUBCASE ("Viewport Properties") {
            CHECK(expected_focal_distance == doctest::Approx(actual_camera.getFocalDistance()));
            CHECK(expected_focal_radius == doctest::Approx(actual_camera.getFocalRadius()));
            CHECK_VECTOR(expected_view_direction, actual_camera.getViewDirection());
            CHECK_VECTOR(expected_up_direction, actual_camera.getUpDirection());
            CHECK_VECTOR(expected_view_horizontal, actual_camera.getViewHorizontal());
            CHECK_VECTOR(expected_view_vertical, actual_camera.getViewVertical());
            CHECK(expected_view_width == doctest::Approx(actual_camera.getViewWidth()));
            CHECK(expected_pixel_width == doctest::Approx(actual_camera.getPixelWidth()));
            CHECK(expected_view_height == doctest::Approx(actual_camera.getViewHeight()));
        }

        SUBCASE ("Pixel Properties") {
            CHECK(expected_pixel_height == doctest::Approx(actual_camera.getPixelHeight()));
            CHECK(expected_vertical_fov == doctest::Approx(actual_camera.getVerticalFOV()));
        }
    }
}

TEST_SUITE ("Camera function tests") {

    TEST_CASE ("Calculate the location of the top left pixel") {

        Point expected_pixel_location =
            expected_view_horizontal * (-0.5 * expected_view_width + 0.5 * expected_pixel_width) +
            expected_view_vertical * (0.5 * expected_view_height - 0.5 * expected_pixel_height) +
            expected_view_direction * (expected_focal_distance);

        Point actual_pixel_location = actual_camera.calculatePixelLocation(0, 0, false);
        CHECK_VECTOR(expected_pixel_location, actual_pixel_location);
    }

    TEST_CASE ("Calculate the location of the bottom left pixel") {

        Point expected_pixel_location =
            expected_view_horizontal * (-0.5 * expected_view_width + 0.5 * expected_pixel_width) +
            -1.0 * expected_view_vertical * (0.5 * expected_view_height - 0.5 * expected_pixel_height) +
            expected_view_direction * (expected_focal_distance);

        Point actual_pixel_location = actual_camera.calculatePixelLocation(expected_image_height - 1, 0, false);
        CHECK_VECTOR(expected_pixel_location, actual_pixel_location);
    }

    TEST_CASE ("Calculate the location of the top right pixel") {

        Point expected_pixel_location =
            -1.0 * expected_view_horizontal * (-0.5 * expected_view_width + 0.5 * expected_pixel_width) +
            expected_view_vertical * (0.5 * expected_view_height - 0.5 * expected_pixel_height) +
            expected_view_direction * (expected_focal_distance);

        Point actual_pixel_location = actual_camera.calculatePixelLocation(0, expected_image_width - 1, false);
        CHECK_VECTOR(expected_pixel_location, actual_pixel_location);
    }

    TEST_CASE ("Calculate the location of the bottom right pixel") {

        Point expected_pixel_location =
            -1.0 * expected_view_horizontal * (-0.5 * expected_view_width + 0.5 * expected_pixel_width) +
            -1.0 * expected_view_vertical * (0.5 * expected_view_height - 0.5 * expected_pixel_height) +
            expected_view_direction * (expected_focal_distance);

        Point actual_pixel_location = actual_camera.calculatePixelLocation(expected_image_height - 1, expected_image_width - 1, false);
        CHECK_VECTOR(expected_pixel_location, actual_pixel_location);
    }

    TEST_CASE ("Tracing ray against a plane aligned with the xz axises") {

        std::shared_ptr<Plane> plane = std::make_shared<Plane>(
            (Point){{0, 0, 0}},
            (Vector<3>){{0, 1, 0}},
            std::make_unique<Diffuse>(RED)
        );

        std::list<std::shared_ptr<Intersectable>> scene = {
            plane
        };

        Ray actual_ray {
            {{0, 1, 0}},
            {{0, -1, 0}}
        };

        SUBCASE ("1 step per sample") {
            Color expected_color = RED;
            Color actual_color = trace(actual_ray, scene, 1);
            CHECK_COLOR(expected_color, actual_color);
        }

        SUBCASE ("2 step per sample") {
            Color expected_color = hadamard(RED, SKY);
            Color actual_color = trace(actual_ray, scene, 2);
            CHECK_COLOR(expected_color, actual_color);
        }
    }

    TEST_CASE ("Tracing a ray against 2 axis-aligned planes") {

        std::shared_ptr<Plane> xz_plane = std::make_shared<Plane>(
            (Point){{0, 0, 0}},
            (Vector<3>){{0, 1, 0}},
            std::make_unique<Metallic>(CORAL, 0.0)
        );

        std::shared_ptr<Plane> xy_plane = std::make_shared<Plane>(
            (Point){{0, 0, 0}},
            (Vector<3>){{0, 0, 1}},
            std::make_unique<Metallic>(LAVENDER, 0.0)
        );

        std::list<std::shared_ptr<Intersectable>> scene = {
            xz_plane,
            xy_plane
        };

        Ray actual_ray {
            {{0, 1, 2}},
            {{0, -1, -1}}
        };

        SUBCASE ("1 step per sample") {
            Color expected_color = CORAL;
            Color actual_color = trace(actual_ray, scene, 1);
            CHECK_COLOR(expected_color, actual_color)
        }

        SUBCASE ("2 step per sample") {
            Color expected_color = hadamard(CORAL, LAVENDER);
            Color actual_color = trace(actual_ray, scene, 2);
            CHECK_COLOR(expected_color, actual_color);
        }

        SUBCASE ("3 step per sample") {
            Color expected_color = hadamard(SKY, hadamard(CORAL, LAVENDER));
            Color actual_color = trace(actual_ray, scene, 3);
            CHECK_COLOR(expected_color, actual_color);
        }
    }
}