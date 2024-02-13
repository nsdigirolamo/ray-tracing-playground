#include <memory>

#include "intersectables/plane.hpp"
#include "intersectables/sphere.hpp"
#include "lib/doctest/doctest.hpp"
#include "materials/diffuse.hpp"
#include "primitives/color.hpp"
#include "ray.hpp"
#include "test/test_utils.hpp"

TEST_SUITE ("Sphere Intersections") {
    TEST_CASE ("Ray intersects sphere.") {

        Sphere sphere {
            {{0, 0, 10}},
            1.0,
            std::make_unique<Diffuse>(RED)
        };

        SUBCASE ("Zero intersections.") {

            Ray ray {
                {{0, 0, 0}},
                {{0, 0, -1}}
            };

            std::optional<Hit> actual_hit = sphere.intersects(ray);

            CHECK_FALSE(actual_hit.has_value());
        }

        SUBCASE ("One intersection.") {

            Ray ray {
                {{1, 0, 0}},
                {{0, 0, 1}}
            };

            std::optional<Hit> actual_hit = sphere.intersects(ray);

            REQUIRE(actual_hit.has_value());

            Ray surface_normal {
                {{1, 0, 10}},
                {{1, 0, 0}}
            };

            Hit expected_hit {
                ray.direction,
                10,
                surface_normal,
                true
            };

            CHECK_HIT(expected_hit, actual_hit.value());
        }

        SUBCASE ("Two intersections.") {

            Ray ray {
                {{0, 0, 0}},
                {{0, 0, 1}}
            };

            std::optional<Hit> actual_hit = sphere.intersects(ray);

            REQUIRE(actual_hit.has_value());

            Ray surface_normal {
                {{0, 0, 9}},
                {{0, 0, -1}}
            };

            Hit expected_hit {
                ray.direction,
                9,
                surface_normal,
                true
            };

            CHECK_HIT(expected_hit, actual_hit.value());
        }

        SUBCASE ("One intersection from within sphere.") {

            Ray ray {
                {{0, 0, 10}},
                {{0, 0, 1}}
            };

            std::optional<Hit> actual_hit = sphere.intersects(ray);

            REQUIRE(actual_hit.has_value());

            Ray surface_normal {
                {{0, 0, 11}},
                {{0, 0, -1}}
            };

            Hit expected_hit {
                ray.direction,
                1,
                surface_normal,
                false
            };

            CHECK_HIT(expected_hit, actual_hit.value());
        }
    }
}

TEST_SUITE ("Plane Intersections") {
    TEST_CASE ("Ray intersects plane.") {

        Plane plane {
            {{0, 0, 0}},
            {{0, 1, 0}},
            std::make_unique<Diffuse>(RED)
        };

        SUBCASE ("Zero intersections.") {

            Ray ray {
                {{0, 1, 0}},
                {{0, 0, 1}}
            };

            std::optional<Hit> actual_hit = plane.intersects(ray);

            CHECK_FALSE(actual_hit.has_value());
        }

        SUBCASE ("One intersection.") {

            Ray ray {
                {{0, 1, 0}},
                {{0, -1, 0}}
            };

            std::optional<Hit> actual_hit = plane.intersects(ray);

            REQUIRE(actual_hit.has_value());

            Ray surface_normal {
                {{0, 0, 0}},
                {{0, 1, 0}}
            };

            Hit expected_hit {
                ray.direction,
                1,
                surface_normal,
                true
            };

            CHECK_HIT(expected_hit, actual_hit.value());
        }

        SUBCASE ("One intersection from behind plane.") {

            Ray ray {
                {{0, -1, 0}},
                {{0, 1, 0}}
            };

            std::optional<Hit> actual_hit = plane.intersects(ray);

            REQUIRE(actual_hit.has_value());

            Ray surface_normal {
                {{0, 0, 0}},
                {{0, -1, 0}}
            };

            Hit expected_hit {
                ray.direction,
                1,
                surface_normal,
                false
            };

            CHECK_HIT(expected_hit, actual_hit.value());
        }
    }
}