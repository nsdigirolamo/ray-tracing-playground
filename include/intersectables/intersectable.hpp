#ifndef INTERSECTABLE_HPP
#define INTERSECTABLE_HPP

#include <optional>

#include "hit.hpp"
#include "materials/material.hpp"
#include "ray.hpp"

#define MINIMUM_INTERSECT_DISTANCE 0.0001

/**
 * @brief An object that can be intersected by a ray in the scene.
 */
class Intersectable {

    public:

        virtual ~Intersectable () {};

        /**
         * @brief Calculates whether or not a given ray has hit the intersectable.
         *
         * @param ray The incoming ray.
         * @return std::optional<Hit>
         */
        virtual std::optional<Hit> intersects (const Ray& ray) const = 0;

        /**
         * @brief Gets the Material of the Intersectable.
         *
         * @return const Material&
         */
        virtual const Material& getMaterial () const = 0;
};

#endif