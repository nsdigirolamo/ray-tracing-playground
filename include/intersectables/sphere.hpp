#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hit.hpp"
#include "intersectables/intersectable.hpp"
#include "materials/material.hpp"
#include "primitives/vector.hpp"
#include "ray.hpp"

class Sphere : public Intersectable {

    private:

        const Point origin;
        const double radius;
        const Material& material;

    public:

        Sphere (const Point& origin, double radius, Material& material);

        std::optional<Hit> intersects (const Ray& ray) const;
        const Material* getMaterial () const;
};

#endif