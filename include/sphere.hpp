#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "point.hpp"
#include "ray.hpp"

class Sphere {

    public:

    Point center;
    double radius;

    Sphere (const Point& center, double radius);
    bool intersects(const Ray& ray);
};

#endif