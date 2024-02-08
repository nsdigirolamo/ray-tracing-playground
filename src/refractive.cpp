#include "materials/refractive.hpp"

Refractive::Refractive (const Color& color, const double refractive_index)
    : color(color)
    , refractive_index(refractive_index)
{ }

Color Refractive::getColor () const {
    return this->color;
}

double Refractive::getRefractiveIndex () const {
    return this->refractive_index;
}

Ray Refractive::scatter (const Hit& hit) const {

    double refraction_ratio = hit.is_front ? 1.0 / this->refractive_index : this->refractive_index;

    double cos_theta = dot((Vector<3>)(-1.0 * hit.incoming), hit.surface_normal.direction);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vector<3> direction;

    if (cannot_refract) {
        direction = reflect(hit.incoming, hit.surface_normal.direction);
    } else {
        direction = refract(hit.incoming, hit.surface_normal.direction, refraction_ratio);
    }

    return {
        hit.surface_normal.origin,
        direction
    };
}