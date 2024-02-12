#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "hit.hpp"
#include "lib/doctest/doctest.hpp"
#include "primitives/matrix.hpp"
#include "primitives/color.hpp"
#include "ray.hpp"

template <unsigned int height, unsigned int width>
void compare_matrix (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            CHECK_MESSAGE((lhs[row, col] == doctest::Approx(rhs[row, col])), "Matrix CHECK for Row: ", row, " Col: ", col);
        }
    }
}

#define compare_ray(lhs, rhs) \
    compare_matrix(lhs.origin, rhs.origin); \
    compare_matrix(lhs.direction, rhs.direction);

#define compare_hit(lhs, rhs) \
    compare_matrix(lhs.incoming, rhs.incoming); \
    CHECK_MESSAGE(lhs.distance == doctest::Approx(rhs.distance), "Hit CHECK for distance"); \
    compare_ray(lhs.surface_normal, rhs.surface_normal); \
    CHECK_MESSAGE(lhs.is_front == rhs.is_front, "Hit CHECK for is_front");

#define compare_color(lhs, rhs) \
    CHECK_MESSAGE(lhs[0] == doctest::Approx(rhs[0]), "Color CHECK for R"); \
    CHECK_MESSAGE(lhs[1] == doctest::Approx(rhs[1]), "Color CHECK for G"); \
    CHECK_MESSAGE(lhs[2] == doctest::Approx(rhs[2]), "Color CHECK for B");

#endif
