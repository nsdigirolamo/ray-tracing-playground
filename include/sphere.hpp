#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "point.hpp"
#include "ray.hpp"

class Sphere {

    public:

    Point center;
    double radius;

    Sphere (const Point& center, double radius) {
        this->center = center;
        this->radius = radius;
    }

    bool intersects(const Ray& ray) {

        // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection#Calculation_using_vectors_in_3D

        Vector<3> ud = unit(ray.direction);
        Vector<3> oc = ray.origin - this->center;

        double discriminant = pow(dot(ud, oc), 2) - (dot(oc, oc) - pow(this->radius, 2));

        return 0 <= discriminant;
    }
};

#endif