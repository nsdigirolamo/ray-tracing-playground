#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "hit.hpp"
#include "primitives/color.hpp"
#include "primitives/vector.hpp"
#include "ray.hpp"

/**
 * @brief A material that can scatter a ray.
 */
class Material {

    public:

        virtual ~Material () {};

        /**
         * @brief Gets the Color of the Material.
         *
         * @return Color
         */
        virtual Color getColor () const = 0;

        /**
         * @brief Generates a scattered ray given some hit on the material.
         *
         * @param hit
         * @return Ray
         */
        virtual Ray scatter (const Hit& hit) const = 0;
};

#endif
