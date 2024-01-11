#include "color.hpp"
#include "hit.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "sphere.hpp"

Sphere::Sphere (const Point& center, double radius)
    : center(center)
    , radius(radius)
{ }

std::optional<Hit> Sphere::intersects(const Ray& ray) const {

    // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection#Calculation_using_vectors_in_3D

    Vector<3> ud = unit(ray.direction);
    Vector<3> oc = ray.origin - this->center;

    double discriminant = pow(dot(ud, oc), 2) - (dot(oc, oc) - pow(this->radius, 2));

    if (0 <= discriminant) {

        double uoc = -1 * dot(ray.direction, (Vector<3>)(ray.origin - this->center));
        double distance = uoc - sqrt(discriminant);

        if (distance < 0) { return {}; }

        Point location = ray.direction * distance + ray.origin;
        Vector<3> normal = location - this->center;
        Color color {{
            255 * ((normal[0] + 1) / 2),
            255 * ((normal[1] + 1) / 2),
            255 * ((normal[2] + 1) / 2)
        }};

        Hit hit = {
            location,
            normal,
            distance,
            color
        };

        return hit;
    }

    return {};
}
