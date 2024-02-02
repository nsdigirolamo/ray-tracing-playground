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

        const Point origin;
        const Vector<3> normal;
        std::unique_ptr<Material> material;

    public:

        Plane (const Point& origin, const Vector<3>& normal, std::unique_ptr<Material> material);

        std::optional<Hit> intersects (const Ray& ray) const;
        const Material& getMaterial () const;
};

#endif