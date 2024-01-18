#include "intersectables/plane.hpp"

Plane::Plane (const Point &origin, const Vector<3> &normal, const Material& material)
    : origin(origin)
    , normal(unit(normal))
    , material(material)
{ }

std::optional<Hit> Plane::intersects (const Ray &ray) const {

    Point plane_origin = this->origin;
    Point ray_origin = ray.origin;

    double denominator = dot(ray.direction, this->normal);

    if (denominator) {

        double distance = dot((Vector<3>)(plane_origin - ray_origin), this->normal) / denominator;

        if (distance < 0) { return {}; }

        Point intersection = ray.direction * distance + ray.origin;
        Ray surface_normal = {intersection, this->normal};
        Hit hit = {distance, surface_normal};

        return hit;
    }

    return {};
}

const Material* Plane::getMaterial () const {
    return &(this->material);
}
