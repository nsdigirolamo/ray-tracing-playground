#ifndef METALLIC_HPP
#define METALLIC_HPP

#include "hit.hpp"
#include "materials/material.hpp"
#include "primitives/color.hpp"
#include "ray.hpp"
#include "random_utils.hpp"

/**
 * @brief A material that scatters rays by reflection.
 */
class Metallic : public Material {

    private:

        const Color color;
        const double blur; /** How blurred the reflection of the metal is. */

    public:

        Metallic (const Color& color, const double blur);

        Color getColor () const;

        /**
         * @brief Generates a reflected ray.
         *
         * @param hit
         * @return Ray
         */
        Ray scatter (const Hit& hit) const;
};

#endif
