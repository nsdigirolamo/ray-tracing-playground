#include "materials/metallic.hpp"

Metallic::Metallic (const Color& color) : color(color) { }

Color Metallic::getColor () const {
    return this->color;
}

Ray Metallic::scatter (const Hit& hit) const {
    return {
        hit.surface_normal.origin,
        reflect(hit.incoming, hit.surface_normal.direction)
    };
}
