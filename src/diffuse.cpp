#include "materials/diffuse.hpp"

Diffuse::Diffuse (const Color& color) : color(color) { }

Color Diffuse::getColor () const {
    return this->color;
}

Ray Diffuse::scatter (const Hit &hit) const {
    return {
        hit.surface_normal.origin,
        hit.surface_normal.direction + randomPointOnUnitSphere()
    };
}
