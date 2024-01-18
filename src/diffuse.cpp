#include "materials/diffuse.hpp"

Diffuse::Diffuse (
    const double absorbance,
    const Color &color
)
    : absorbance(absorbance)
    , color(color)
{ }

double Diffuse::getAbsorbance () const {
    return this->absorbance;
}

Color Diffuse::getColor () const {
    return this->color;
}

Ray Diffuse::scatter (const Hit &hit) const {

    return hit.surface_normal;

}
