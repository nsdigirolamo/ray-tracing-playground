#include "lib/catch2/catch.hpp"
#include "hit.hpp"
#include "sphere.hpp"
#include "test/test_utils.hpp"

/**
 * This file does not test for a hit's color (yet)
 */

TEST_CASE ("sphere intersection detects hits and misses") {

    SECTION ("two intersections") {

        Ray ray = {
            {{0, 0, 0}},
            {{0, 0, 1}}
        };

        GIVEN ("a ray directed towards a sphere") {

            Sphere sphere = {
                {{0, 0, 10.0}},
                1.0
            };

            WHEN ("the intersect function is called") {

                std::optional<Hit> result = sphere.intersects(ray);

                THEN ("the intersect function returns a hit") {

                    REQUIRE(result);

                } AND_THEN("the hit occurs at the closest location with the correct normal") {

                    Hit hit = {
                        {{0, 0, 9}},
                        {{0, 0, -1}},
                        9,
                        {{0, 0, 0}}
                    };

                    compare_matrix(result.value().location, hit.location);
                    compare_matrix(result.value().normal, hit.normal);
                    CHECK(result.value().distance == Approx(hit.distance));
                }
            }

        } AND_GIVEN("a ray directed away from a sphere") {

            Sphere sphere = {
                {{0, 0, -10.0}},
                1.0
            };

            WHEN ("the intersect function is called") {

                std::optional<Hit> result = sphere.intersects(ray);

                THEN("the hit does not exist") {

                    CHECK_FALSE(result);

                }
            }
        }
    }

    SECTION ("one intersection") {

        Ray ray = {
            {{0, 0, 0}},
            {{0, 0, 1}}
        };

        GIVEN ("a ray directed towards a sphere") {

            Sphere sphere = {
                {{1.0, 0, 10.0}},
                1.0
            };

            WHEN ("the intersect function is called") {

                std::optional<Hit> result = sphere.intersects(ray);

                THEN ("the intersect function returns a hit") {

                    REQUIRE(result);

                } AND_THEN("the hit occurs at the location with the correct normal") {

                    Hit hit = {
                        {{0, 0, 10.0}},
                        {{-1, 0, 0}},
                        10,
                        {{0, 0, 0}}
                    };

                    REQUIRE(result);
                    compare_matrix(result.value().location, hit.location);
                    compare_matrix(result.value().normal, hit.normal);
                    CHECK(result.value().distance == Approx(hit.distance));
                }
            }
        } AND_GIVEN("a ray directed away from a sphere") {

            Sphere sphere = {
                {{1.0, 0, -10.0}},
                1.0
            };

            WHEN ("the intersect function is called") {

                std::optional<Hit> result = sphere.intersects(ray);

                THEN("the hit does not exist") {

                    CHECK_FALSE(result);

                }
            }
        }
    }

    SECTION ("no intersection") {

        Ray ray = {
            {{0, 0, 0}},
            {{1, 0, 1}}
        };

        GIVEN ("a ray misdirected towards a sphere") {

            Sphere sphere = {
                {{0, 0, 10.0}},
                1.0
            };

            WHEN ("the intersect function is called") {

                std::optional<Hit> result = sphere.intersects(ray);

                THEN("the hit does not exist") {

                    CHECK_FALSE(result);

                }
            }
        }
    }
}