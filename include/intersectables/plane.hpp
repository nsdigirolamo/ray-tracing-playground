#ifndef PLANE_HPP
#define PLANE_HPP

#include <memory>

#include "hit.hpp"
#include "intersectables/intersectable.hpp"
#include "materials/material.hpp"
#include "primitives/vector.hpp"
#include "ray.hpp"

class Plane : public Intersectable {

    private:

        const Point origin; /** The plane's location in the scene. */
        const UnitVector<3> normal; /** The plane's surface normal. */
        std::unique_ptr<Material> material; /** The plane's material. */

    public:

        Plane (const Point& origin, const UnitVector<3>& normal, std::unique_ptr<Material> material);

        std::optional<Hit> intersects (const Ray& ray) const;
        const Material& getMaterial () const;
};

#endif