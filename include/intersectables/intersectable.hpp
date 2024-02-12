#ifndef INTERSECTABLE_HPP
#define INTERSECTABLE_HPP

#include <optional>

#include "hit.hpp"
#include "materials/material.hpp"
#include "ray.hpp"

#define MINIMUM_INTERSECT_DISTANCE 0.0001

class Intersectable {

    public:

        virtual ~Intersectable () {};

        virtual std::optional<Hit> intersects (const Ray& ray) const = 0;
        virtual const Material& getMaterial () const = 0;
};

#endif