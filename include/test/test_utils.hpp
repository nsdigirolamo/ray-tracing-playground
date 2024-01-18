#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "hit.hpp"
#include "lib/catch2/catch.hpp"
#include "primitives/matrix.hpp"
#include "ray.hpp"

template <unsigned int height, unsigned int width>
void compare_matrix (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            CHECK(lhs[row, col] == Approx(rhs[row, col]));
        }
    }
}

void compare_ray (const Ray& lhs, const Ray& rhs);
void compare_hit (const Hit& lhs, const Hit& rhs);

#endif
