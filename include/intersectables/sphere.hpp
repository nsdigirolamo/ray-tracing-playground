#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <memory>

#include "hit.hpp"
#include "intersectables/intersectable.hpp"
#include "materials/material.hpp"
#include "primitives/vector.hpp"
#include "ray.hpp"

class Sphere : public Intersectable {

    private:

        const Point origin; /** The sphere's location in space. */
        const double radius; /** The sphere's radius. */
        std::unique_ptr<Material> material; /** The sphere's material. */

    public:

        Sphere (const Point& origin, double radius, std::unique_ptr<Material> material);

        std::optional<Hit> intersects (const Ray& ray) const;
        const Material& getMaterial () const;
};

#endif