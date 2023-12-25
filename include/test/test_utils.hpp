#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "lib/catch2/catch.hpp"
#include "matrix.hpp"

template <unsigned int height, unsigned int width>
void compare_matrix (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            CHECK(lhs[row, col] == Approx(rhs[row, col]));
        }
    }
}

#endif
