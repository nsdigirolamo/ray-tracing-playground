#include "intersectables/plane.hpp"

const double minimum_distance = 0.0001;

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

        if (distance < minimum_distance) { return {}; }

        Point intersection = ray.direction * distance + ray.origin;
        Ray surface_normal = {intersection, this->normal};
        Hit hit = {ray.direction, distance, surface_normal};

        return hit;
    }

    return {};
}

const Material* Plane::getMaterial () const {
    return &(this->material);
}
