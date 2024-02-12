#include <cmath>
#include <memory>
#include <optional>

#include "intersectables/plane.hpp"
#include "lib/doctest/doctest.hpp"
#include "materials/metallic.hpp"
#include "primitives/color.hpp"
#include "primitives/vector.hpp"
#include "ray.hpp"
#include "test/test_utils.hpp"

TEST_SUITE ("Vector Construction Tests") {

    TEST_CASE ("Default Initialization") {

        Vector<3> actual_vector;

        for (int row = 0; row < 3; ++row) {
            CHECK(0.0 == doctest::Approx(actual_vector[row]));
        }
    }

    TEST_CASE ("Array Initialization") {

        double expected_values[3] {1, 2, 3};
        Vector<3> actual_vector { expected_values };

        for (int row = 0; row < 3; ++row) {
            CHECK(expected_values[row] == doctest::Approx(actual_vector[row]));
        }

        SUBCASE ("The array used for initialization can be changed without changing the matrix.") {
            expected_values[0] = 10.0;
            CHECK_FALSE(expected_values[0] == doctest::Approx(actual_vector[0]));
        }
    }

    TEST_CASE ("Matrix Initialization") {

        Matrix<3,1> expected_matrix {{
            {1},
            {2},
            {3}
        }};
        Vector<3> actual_vector { expected_matrix };

        compare_matrix(expected_matrix, actual_vector);
    }
}

TEST_SUITE ("Vector Arithmetic Tests") {

    Vector<3> lhs {{1, 2, 3}};
    Vector<3> rhs {{4, 5, 6}};

    TEST_CASE ("Vector Dot Product") {
        double expected_dot_product = 32;
        double actual_dot_product = dot(lhs, rhs);
        CHECK(expected_dot_product == doctest::Approx(actual_dot_product));
    }

    TEST_CASE ("Vector Cross Product") {
        Vector<3> expected_cross_product = {{-3, 6, -3}};
        Vector<3> actual_cross_product = cross(lhs, rhs);
        CHECK(expected_cross_product == actual_cross_product);
    }
}

TEST_SUITE ("Vector Property Tests") {

    Vector<3> vector {{1, 2, 3}};

    TEST_CASE ("Vector Length Squared") {
        double expected_length = 14;
        double actual_length = length_squared(vector);
        CHECK(expected_length == doctest::Approx(actual_length));
    }

    TEST_CASE ("Vector Length") {
        double expected_length = 3.74165738677;
        double actual_length = length(vector);
        CHECK(expected_length == doctest::Approx(actual_length));
    }

    TEST_CASE ("Unit Vector") {
        Vector<3> expected_unit = {{1.0 / length(vector), 2.0 / length(vector), 3.0 / length(vector)}};
        Vector<3> actual_unit = unit(vector);
        compare_matrix(expected_unit, actual_unit);
    }
}

TEST_SUITE ("Specialized Vector Operations") {

    TEST_CASE ("Vector Reflection") {

        Vector<3> incoming {{1, -1, 0}};
        Vector<3> surface_normal {{0, 1, 0}};
        Vector<3> expected_reflected {{1, 1, 0}};
        Vector<3> actual_reflected = reflect(incoming, surface_normal);
        compare_matrix(expected_reflected, actual_reflected);

        Plane plane {
                {{0, 0, 0}},
                {{0, 1, 0}},
                std::make_unique<Metallic>(RED, 0)
            };

        SUBCASE ("Reflection Off Plane") {

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
            compare_ray(expected_scattered, actual_scattered)
        }

        SUBCASE ("Reflected Off Plane Backside") {

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
            compare_ray(expected_scattered, actual_scattered)
        }
    }

    TEST_CASE ("Vector Refraction") {
        // TODO
    }
}