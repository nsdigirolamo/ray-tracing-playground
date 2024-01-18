#include "hit.hpp"
#include "intersectables/sphere.hpp"
#include "lib/catch2/catch.hpp"
#include "materials/diffuse.hpp"
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

            Diffuse material = {
                0.5,
                {{255, 255, 255}}
            };

            Sphere sphere = {
                {{0, 0, 10.0}},
                1.0,
                material
            };

            WHEN ("the intersect function is called") {

                std::optional<Hit> result = sphere.intersects(ray);

                THEN ("the intersect function returns a hit") {

                    REQUIRE(result);

                } AND_THEN("the hit occurs at the closest location with the correct normal") {

                    Ray surface_normal = {
                        {{0, 0, 9}},
                        {{0, 0, -1}}
                    };

                    Hit hit = {
                        9,
                        surface_normal
                    };

                    compare_ray(result.value().surface_normal, surface_normal);
                    CHECK(result.value().distance == Approx(hit.distance));
                }
            }

        } AND_GIVEN("a ray directed away from a sphere") {

            Diffuse material = {
                0.5,
                {{255, 255, 255}}
            };

            Sphere sphere = {
                {{0, 0, -10.0}},
                1.0,
                material
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

            Diffuse material = {
                0.5,
                {{255, 255, 255}}
            };

            Sphere sphere = {
                {{1.0, 0, 10.0}},
                1.0,
                material
            };

            WHEN ("the intersect function is called") {

                std::optional<Hit> result = sphere.intersects(ray);

                THEN ("the intersect function returns a hit") {

                    REQUIRE(result);

                } AND_THEN("the hit occurs at the location with the correct normal") {

                    Ray surface_normal = {
                        {{0, 0, 10.0}},
                        {{-1, 0, 0}},
                    };

                    Hit hit = {
                        10,
                        surface_normal
                    };

                    REQUIRE(result);
                    compare_ray(result.value().surface_normal, surface_normal);
                    CHECK(result.value().distance == Approx(hit.distance));
                }
            }
        } AND_GIVEN("a ray directed away from a sphere") {

            Diffuse material = {
                0.5,
                {{255, 255, 255}}
            };

            Sphere sphere = {
                {{1.0, 0, -10.0}},
                1.0,
                material
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

            Diffuse material = {
                0.5,
                {{255, 255, 255}}
            };

            Sphere sphere = {
                {{0, 0, 10.0}},
                1.0,
                material
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