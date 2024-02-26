#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "hit.hpp"
#include "lib/doctest/doctest.hpp"
#include "primitives/matrix.hpp"
#include "primitives/color.hpp"
#include "ray.hpp"

#define CHECK_MATRIX(lhs, rhs) \
    REQUIRE(lhs.height() == rhs.height()); \
    REQUIRE(lhs.width() == rhs.width()); \
    for (int row = 0; row < lhs.height(); ++row) { \
        for (int col = 0; col < lhs.width(); ++col) { \
            CAPTURE(row); \
            CAPTURE(col); \
            CHECK(lhs[row][col] == doctest::Approx(rhs[row][col])); \
        } \
    }

#define CHECK_VECTOR(lhs, rhs) \
    REQUIRE(lhs.height() == rhs.height()); \
    REQUIRE(lhs.width() == 1); \
    REQUIRE(lhs.width() == rhs.width()); \
    for (int row = 0; row < lhs.height(); ++ row) { \
        CAPTURE(row); \
        CHECK(lhs[row] == doctest::Approx(rhs[row])); \
    }

#define CHECK_RAY(lhs, rhs) \
    CHECK_VECTOR(lhs.origin, rhs.origin); \
    CHECK_VECTOR(lhs.direction, rhs.direction);

#define CHECK_HIT(lhs, rhs) \
    CHECK_VECTOR(lhs.incoming, rhs.incoming); \
    CHECK(lhs.distance == doctest::Approx(rhs.distance)); \
    CHECK_RAY(lhs.surface_normal, rhs.surface_normal); \
    CHECK(lhs.is_front == rhs.is_front);

#define CHECK_COLOR(lhs, rhs) \
    CHECK(lhs[0] == doctest::Approx(rhs[0])); \
    CHECK(lhs[1] == doctest::Approx(rhs[1])); \
    CHECK(lhs[2] == doctest::Approx(rhs[2]));

#endif
