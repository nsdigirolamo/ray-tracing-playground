#include "camera.hpp"
#include "lib/doctest/doctest.hpp"
#include "primitives/matrix.hpp"
#include "primitives/vector.hpp"
#include "test/test_utils.hpp"

TEST_SUITE ("Camera Construction Tests") {

    TEST_CASE ("Simple Camera Construction") {

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

        CHECK_VECTOR(expected_location, actual_camera.getLocation());
        CHECK(expected_image_height == actual_camera.getImageHeight());
        CHECK(expected_image_width == actual_camera.getImageWidth());
        CHECK(expected_focal_distance == doctest::Approx(actual_camera.getFocalDistance()));
        CHECK(expected_focal_radius == doctest::Approx(actual_camera.getFocalRadius()));
        CHECK_VECTOR(expected_view_direction, actual_camera.getViewDirection());
        CHECK_VECTOR(expected_up_direction, actual_camera.getUpDirection());
        CHECK_VECTOR(expected_view_horizontal, actual_camera.getViewHorizontal());
        CHECK_VECTOR(expected_view_vertical, actual_camera.getViewVertical());
        CHECK(expected_view_width == doctest::Approx(actual_camera.getViewWidth()));
        CHECK(expected_pixel_width == doctest::Approx(actual_camera.getPixelWidth()));
        CHECK(expected_view_height == doctest::Approx(actual_camera.getViewHeight()));
        CHECK(expected_pixel_height == doctest::Approx(actual_camera.getPixelHeight()));
        CHECK(expected_vertical_fov == doctest::Approx(actual_camera.getVerticalFOV()));

        SUBCASE ("Calculate the location of the top left pixel.") {

            Point expected_pixel_location =
                expected_view_horizontal * (-0.5 * expected_view_width + 0.5 * expected_pixel_width) +
                expected_view_vertical * (0.5 * expected_view_height - 0.5 * expected_pixel_height) +
                expected_view_direction * (expected_focal_distance);

            Point actual_pixel_location = actual_camera.calculatePixelLocation(0, 0, false);

            CHECK_VECTOR(expected_pixel_location, actual_pixel_location);
        }
    }
}