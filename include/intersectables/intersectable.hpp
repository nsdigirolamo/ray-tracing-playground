#ifndef INTERSECTABLE_HPP
#define INTERSECTABLE_HPP

#include <optional>

#include "hit.hpp"
#include "materials/material.hpp"
#include "ray.hpp"

class Intersectable {

    public:

        virtual std::optional<Hit> intersects (const Ray& ray) const = 0;
        virtual const Material* getMaterial () const = 0;
};

#endif