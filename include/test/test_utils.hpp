#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "matrix.hpp"
#include "test/test_utils.hpp"

#define EPSILON 0.0001

template <unsigned int height, unsigned int width>
void compare_matrix(Matrix<height, width> m1, Matrix<height, width> m2) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < height; col++) {
            CHECK(m1[row, col] == m2[row, col]);
        }
    }
}

#endif
