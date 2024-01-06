#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <optional>

#include "hit.hpp"
#include "point.hpp"
#include "ray.hpp"

class Sphere {

    public:

    Point center;
    double radius;

    Sphere (const Point &center, double radius);
    std::optional<Hit> intersects(const Ray &ray) const;
};

#endif