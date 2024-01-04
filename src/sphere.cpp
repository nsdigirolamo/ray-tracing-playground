#include "sphere.hpp"

Sphere::Sphere (const Point& center, double radius) {
    this->center = center;
    this->radius = radius;
}

Color Sphere::intersects(const Ray& ray) const {

    // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection#Calculation_using_vectors_in_3D

    Vector<3> ud = unit(ray.direction);
    Vector<3> oc = ray.origin - this->center;

    double discriminant = pow(dot(ud, oc), 2) - (dot(oc, oc) - pow(this->radius, 2));

    if (0 <= discriminant) {
        return {{255, 0, 0}};
    } else {
        return {{0, 0, 0}};
    }
}
