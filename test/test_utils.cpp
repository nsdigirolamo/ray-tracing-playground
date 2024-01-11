#include "test/test_utils.hpp"

void compare_ray (const Ray& lhs, const Ray& rhs) {
    compare_matrix(lhs.origin, rhs.origin);
    compare_matrix(lhs.direction, rhs.direction);
}

void compare_hit (const Hit& lhs, const Hit& rhs) {
    compare_matrix(lhs.location, rhs.location);
    compare_matrix(lhs.normal, rhs.normal);
    CHECK(lhs.distance == Approx(rhs.distance));
    compare_matrix(lhs.color, rhs.color);
}