#include "intersectables/plane.hpp"

Plane::Plane (const Point& origin, const UnitVector<3>& normal, std::unique_ptr<Material> material)
    : origin(origin)
    , normal(normal)
    , material(std::move(material))
{ }

std::optional<Hit> Plane::intersects (const Ray &ray) const {

    Point plane_origin = this->origin;
    Point ray_origin = ray.origin;

    double denominator = dot(ray.direction, this->normal);

    if (denominator) {

        double distance = dot((Vector<3>)(plane_origin - ray_origin), this->normal) / denominator;

        if (distance < MINIMUM_INTERSECT_DISTANCE) { return {}; }

        Point intersection = ray.direction * distance + ray.origin;
        bool is_front = dot(ray.direction, this->normal) <= 0;

        Ray surface_normal = is_front ? (Ray){intersection, this->normal} : (Ray){intersection, -1.0 * this->normal};

        Hit hit = {
            ray.direction,
            distance,
            surface_normal,
            is_front
        };

        return hit;
    }

    return {};
}

const Material& Plane::getMaterial () const {
    return *(this->material);
}
