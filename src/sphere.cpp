#include "sphere.hpp"

Sphere::Sphere (const Point& center, double radius) {
    this->center = center;
    this->radius = radius;
}

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

        Ray normal = {
            location,
            location - this->center
        };

        Color color {{
            255 * ((normal.direction[0] + 1) / 2),
            255 * ((normal.direction[1] + 1) / 2),
            255 * ((normal.direction[2] + 1) / 2)
        }};

        Hit hit = {
            location,
            normal,
            color
        };

        return hit;

    }

    return {};
}
