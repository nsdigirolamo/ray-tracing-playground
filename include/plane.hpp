#ifndef PLANE_HPP
#define PLANE_HPP

#include "intersectable.hpp"
#include "point.hpp"
#include "vector.hpp"

class Plane : public Intersectable {

    private:

    const Point origin;
    const Vector<3> normal;

    public:

    Plane (const Point &origin, const Vector<3> &normal);
    std::optional<Hit> intersects (const Ray &ray) const;
};

#endif