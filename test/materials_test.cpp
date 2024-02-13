#include "hit.hpp"
#include "intersectables/plane.hpp"
#include "lib/doctest/doctest.hpp"
#include "materials/metallic.hpp"
#include "ray.hpp"
#include "test/test_utils.hpp"

TEST_SUITE ("Diffuse Material Tests") {
    // TODO
}

TEST_SUITE ("Metallic Material Tests") {

    TEST_CASE ("Plane Metallic Scatter Test") {

        Color expected_color = RED;

        Plane plane {
            {{0, 0, 0}},
            {{0, 1, 0}},
            std::make_unique<Metallic>(expected_color, 0)
        };

        Ray incoming {
            {{-1, 1, 0}},
            {{1, -1, 0}}
        };

        Hit expected_hit {
            {{1, -1, 0}},
            sqrt(2),
            {
                {{0, 0, 0}},
                {{0, 1, 0}}
            },
            true
        };

        std::optional<Hit> actual_hit = plane.intersects(incoming);

        REQUIRE(actual_hit.has_value());
        compare_hit(expected_hit, actual_hit.value());

        Ray expected_scattered {
            {{0, 0, 0}},
            {{1, 1, 0}}
        };

        Ray actual_scattered = plane.getMaterial().scatter(actual_hit.value());
        compare_ray(expected_scattered, actual_scattered);

        Color actual_color = plane.getMaterial().getColor();
        compare_color(expected_color, actual_color);

        SUBCASE ("Scatter on plane backside.") {

            Ray incoming {
                {{-1, -1, 0}},
                {{1, 1, 0}}
            };

            Hit expected_hit {
                {{1, 1, 0}},
                sqrt(2),
                {
                    {{0, 0, 0}},
                    {{0, -1, 0}}
                },
                false
            };

            std::optional<Hit> actual_hit = plane.intersects(incoming);

            REQUIRE(actual_hit.has_value());
            compare_hit(expected_hit, actual_hit.value());

            Ray expected_scattered {
                {{0, 0, 0}},
                {{1, -1, 0}}
            };

            Ray actual_scattered = plane.getMaterial().scatter(actual_hit.value());
            compare_ray(expected_scattered, actual_scattered);

            Color actual_color = plane.getMaterial().getColor();
            compare_color(expected_color, actual_color);
        }
    }
}

TEST_SUITE ("Refractive Material Tests") {
    // TODO
}