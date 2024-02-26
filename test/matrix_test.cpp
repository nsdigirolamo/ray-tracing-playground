#include <cmath>

#include "lib/doctest/doctest.hpp"
#include "primitives/matrix.hpp"
#include "test/test_utils.hpp"

TEST_SUITE ("Matrix Construction Tests") {

    TEST_CASE ("Default Initialization") {

        Matrix<3,3> actual_matrix;

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                CHECK(0.0 == doctest::Approx(actual_matrix[row][col]));
            }
        }
    }

    TEST_CASE ("Array Initialization") {

        double expected_values[3][3] {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        Matrix<3, 3> actual_matrix { expected_values };

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                CHECK(expected_values[row][col] == doctest::Approx(actual_matrix[row][col]));
            }
        }

        SUBCASE ("The array used for initialization can be changed without changing the matrix.") {
            expected_values[0][0] = 10.0;
            CHECK_FALSE(expected_values[0][0] == doctest::Approx(actual_matrix[0][0]));
        }
    }

    TEST_CASE ("Matrix Initialization") {

        double expected_values[3][3] {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        Matrix<3,3> original_matrix { expected_values };
        Matrix<3,3> actual_matrix = original_matrix;

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                CHECK(expected_values[row][col] == doctest::Approx(actual_matrix[row][col]));
            }
        }

        SUBCASE ("The matrix used for initialization can be changed without changing the matrix.") {
            original_matrix *= 5;
            CHECK_FALSE(original_matrix[0][0] == doctest::Approx(actual_matrix[0][0]));
        }
    }
}

TEST_SUITE ("Matrix Arithmetic Tests") {

    Matrix<3,3> lhs {{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    }};

    Matrix<3,3> rhs {{
        {2, 3, 4},
        {5, 6, 7},
        {8, 9, 10}
    }};

    double scalar = 10;

    TEST_CASE ("Matrix Addition") {

        Matrix<3,3> expected_sum_matrix {{
            {3, 5, 7},
            {9, 11, 13},
            {15, 17, 19}
        }};

        SUBCASE ("+= operation") {
            Matrix<3,3> actual_matrix = lhs;
            actual_matrix += rhs;
            CHECK_MATRIX(expected_sum_matrix, actual_matrix);
        }

        SUBCASE ("+ operation") {
            Matrix<3,3> actual_matrix = lhs + rhs;
            CHECK_MATRIX(expected_sum_matrix, actual_matrix);
        }
    }

    TEST_CASE ("Matrix Subtraction") {

        Matrix<3,3> expected_difference_matrix {{
            {-1, -1, -1},
            {-1, -1, -1},
            {-1, -1, -1}
        }};

        SUBCASE ("-= operation") {
            Matrix<3,3> actual_matrix = lhs;
            actual_matrix -= rhs;
            CHECK_MATRIX(expected_difference_matrix, actual_matrix);
        }

        SUBCASE ("- operation") {
            Matrix<3,3> actual_matrix = lhs - rhs;
            CHECK_MATRIX(expected_difference_matrix, actual_matrix);
        }
    }

    TEST_CASE ("Matrix Scalar Multiplication") {

        Matrix<3,3> expected_product_matrix {{
            {10, 20, 30},
            {40, 50, 60},
            {70, 80, 90}
        }};

        SUBCASE ("*= operation") {
            Matrix<3,3> actual_matrix = lhs;
            actual_matrix *= scalar;
            CHECK_MATRIX(expected_product_matrix, actual_matrix);
        }

        SUBCASE ("* operation") {
            Matrix<3,3> actual_matrix = scalar * lhs;
            CHECK_MATRIX(expected_product_matrix, actual_matrix);
        }
    }

    TEST_CASE ("Matrix Scalar Division") {

        Matrix<3,3> expected_quotient_matrix {{
            {0.1, 0.2, 0.3},
            {0.4, 0.5, 0.6},
            {0.7, 0.8, 0.9}
        }};

        SUBCASE ("/= operation") {
            Matrix<3,3> actual_matrix = lhs;
            actual_matrix /= scalar;
            CHECK_MATRIX(expected_quotient_matrix, actual_matrix);
        }

        SUBCASE ("/ operation") {
            Matrix<3,3> actual_matrix = lhs / scalar;
            CHECK_MATRIX(expected_quotient_matrix, actual_matrix);
        }
    }

    TEST_CASE ("Matrix Hadamard Product") {

        Matrix<3,3> expected_product_matrix {{
            {2, 6, 12},
            {20, 30, 42},
            {56, 72, 90}
        }};

        Matrix<3,3> actual_matrix = hadamard(lhs, rhs);
        CHECK_MATRIX(expected_product_matrix, actual_matrix);
    }
}

TEST_SUITE ("Matrix Transform Tests") {

    Matrix<3,3> identity_matrix {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};

    const double theta = M_PI / 2.0;

    Matrix<3,3> y_rotation_matrix {{
        {cos(theta), 0, sin(theta)},
        {0, 1, 0},
        {-1.0 * sin(theta), 0, cos(theta)}
    }};

    Matrix<3, 1> vector {{
        {0},
        {0},
        {1}
    }};

    TEST_CASE ("Identity Transformation") {
        Matrix<3, 1> expected_vector {{
            {0},
            {0},
            {1}
        }};
        Matrix<3, 1> actual_vector = identity_matrix.transform(vector);
        CHECK_MATRIX(expected_vector, actual_vector);
    }

    TEST_CASE ("90 Degree Rotation Transformation") {
        Matrix<3, 1> expected_vector = {{
            {1},
            {0},
            {0}
        }};
        Matrix<3, 1> actual_vector = y_rotation_matrix.transform(vector);
        CHECK_MATRIX(expected_vector, actual_vector);
    }
}

TEST_SUITE ("Matrix Comparison Tests") {

    Matrix<3, 3> lhs {{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    }};

    Matrix<3, 3> rhs {{
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    }};

    Matrix<3, 3> rhs_approx {{
        {1.0001, 2.0001, 3.0001},
        {4.0001, 5.0001, 6.0001},
        {7.0001, 8.0001, 9.0001}
    }};

    Matrix<3, 3> rhs_not_approx {{
        {1.1, 2.0001, 3.0001},
        {4.0001, 5.0001, 6.0001},
        {7.0001, 8.0001, 9.0001}
    }};

    TEST_CASE ("Matrix Equals Itself") {

        CHECK(lhs == lhs);

        SUBCASE ("!= operator") {
            CHECK_FALSE(lhs != lhs);
        }
    }

    TEST_CASE ("Matrix Does Not Equal Matrix With Different Values") {

        CHECK_FALSE(lhs == rhs);

        SUBCASE ("!= operator") {
            CHECK(lhs != rhs);
        }
    }

    TEST_CASE ("Matrix Equals Different Matrix With Same Values") {

        Matrix<3,3> same_lhs = lhs;
        CHECK(lhs == same_lhs);

        SUBCASE ("!= operator") {
            CHECK_FALSE(lhs != same_lhs);
        }
    }

    TEST_CASE ("Matrices Are Approx") {
        CHECK(isApprox(lhs, rhs_approx));
    }

    TEST_CASE ("Matrices Are Not Approx") {
        CHECK_FALSE(isApprox(lhs, rhs_not_approx));
    }
}