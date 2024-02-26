#include <cmath>
#include <memory>
#include <optional>

#include "lib/doctest/doctest.hpp"
#include "primitives/vector.hpp"
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

        for (int row = 0; row < 3; ++row) {
            CHECK(expected_matrix[row][0] == doctest::Approx(actual_vector[row]));
        }
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
        double actual_length = vector.length_squared();
        CHECK(expected_length == doctest::Approx(actual_length));
    }

    TEST_CASE ("Vector Length") {
        double expected_length = 3.74165738677;
        double actual_length = vector.length();
        CHECK(expected_length == doctest::Approx(actual_length));
    }

    TEST_CASE ("Unit Vector") {
        Vector<3> expected_unit = {{1.0 / vector.length(), 2.0 / vector.length(), 3.0 / vector.length()}};
        Vector<3> actual_unit = normalize(vector);
        CHECK_VECTOR(expected_unit, actual_unit);
    }
}

TEST_SUITE ("Specialized Vector Operations") {

    TEST_CASE ("Vector Reflection") {
        Vector<3> incoming {{1, -1, 0}};
        Vector<3> surface_normal {{0, 1, 0}};
        Vector<3> expected_reflected {{1, 1, 0}};
        Vector<3> actual_reflected = reflect(incoming, surface_normal);
        CHECK_VECTOR(expected_reflected, actual_reflected);
    }

    TEST_CASE ("Vector Refraction") {
        // TODO
    }
}