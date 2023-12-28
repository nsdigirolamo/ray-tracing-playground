#include "lib/catch2/catch.hpp"
#include "test/test_utils.hpp"

#include "sphere.hpp"
#include "ray.hpp"
#include "vector.hpp"

TEST_CASE ("sphere intersection detects hits and misses") {

    SECTION ("two intersections") {
        GIVEN ("a ray directly intersects a sphere") {

            Sphere sphere = {
                {{0, 0, 0}},
                1.0
            };

            Ray ray = {
                {{0, 0, 10}},
                {{0, 0, 1}}
            };

            WHEN ("the intersection occurs") {
                THEN ("the intersect function returns true") {

                    CHECK(sphere.intersects(ray));
                }
            }
        } AND_GIVEN ("a ray indirectly intersects a sphere") {

            Sphere sphere = {
                {{0, 0, 0}},
                1.0
            };

            Ray ray = {
                {{0, 0, 1.1}},
                {{1, 1, 1}}
            };

            WHEN ("the intersection occurs") {
                THEN ("the intersect function returns true") {

                    CHECK(sphere.intersects(ray));
                }
            }
        }
    }

    SECTION ("one intersection") {
        GIVEN ("a ray intersects with a sphere tangentally") {

            Sphere sphere = {
                {{0, 0, 0}},
                1.0
            };

            Ray ray = {
                {{1, 0, 10}},
                {{0, 0, 1}}
            };

            WHEN ("the intersection occurs") {
                THEN ("the intersect function returns true") {

                    CHECK(sphere.intersects(ray));
                }
            }
        }
    }

    SECTION ("no intersection") {
        GIVEN ("a ray does not intersect with a sphere") {

            Sphere sphere = {
                {{0, 0, 0}},
                1.0
            };

            Ray ray = {
                {{10, 0, 10}},
                {{0, 0, 1}}
            };

            WHEN ("the intersection occurs") {
                THEN ("the intersect function returns false") {

                    CHECK_FALSE(sphere.intersects(ray));
                }
            }
        }
    }
}