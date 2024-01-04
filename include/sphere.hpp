#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "color.hpp"
#include "point.hpp"
#include "ray.hpp"

class Sphere {

    public:

    Point center;
    double radius;

    Sphere (const Point &center, double radius);
    Color intersects(const Ray &ray) const;
};

#endif