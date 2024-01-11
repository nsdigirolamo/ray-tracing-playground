#include "color.hpp"
#include "hit.hpp"
#include "plane.hpp"
#include "ray.hpp"

Plane::Plane (const Point &origin, const Vector<3> &normal)
    : origin(origin)
    , normal(unit(normal))
{ }

std::optional<Hit> Plane::intersects (const Ray &ray) const {

    Point plane_origin = this->origin;
    Point ray_origin = ray.origin;

    double denominator = dot(ray.direction, this->normal);

    if (denominator) {

        double distance = dot((Vector<3>)(plane_origin - ray_origin), this->normal) / denominator;

        if (distance < 0) { return {}; }

        Point location = ray.direction * distance + ray.origin;

        Color color {{
            255 * ((this->normal[0] + 1) / 2),
            255 * ((this->normal[1] + 1) / 2),
            255 * ((this->normal[2] + 1) / 2)
        }};

        Hit hit = {
            location,
            this->normal,
            distance,
            color
        };

        return hit;
    }

    return {};
}