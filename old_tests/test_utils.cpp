#include "test/test_utils.hpp"

void compare_ray (const Ray& lhs, const Ray& rhs) {
    compare_matrix(lhs.origin, rhs.origin);
    compare_matrix(lhs.direction, rhs.direction);
}

void compare_hit (const Hit& lhs, const Hit& rhs) {
    compare_matrix(lhs.incoming, rhs.incoming);
    CHECK(lhs.distance == Approx(rhs.distance));
    compare_ray(lhs.surface_normal, rhs.surface_normal);
}

void compare_color (const Color& lhs, const Color& rhs) {
    for (int row = 0; row < 3; ++row) {
        CHECK(lhs[row] == Approx(rhs[row]));
    }
}