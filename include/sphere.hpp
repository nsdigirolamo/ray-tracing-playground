#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "intersectable.hpp"

class Sphere : public Intersectable {

    public:

    const Point center;
    const double radius;

    Sphere (const Point &center, double radius);
    std::optional<Hit> intersects (const Ray &ray) const;
};

#endif