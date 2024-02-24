#ifndef REFRACTIVE_HPP
#define REFRACTIVE_HPP

#include <cmath>

#include "hit.hpp"
#include "materials/material.hpp"
#include "primitives/color.hpp"
#include "primitives/unit_vector.hpp"
#include "primitives/vector.hpp"
#include "random_utils.hpp"
#include "ray.hpp"

/**
 * @brief A material that scatters rays by refraction.
 */
class Refractive : public Material {

    private:

        const Color color;
        const double refractive_index; /** The refractive index of the material. */

    public:

        Refractive (const Color& color, const double refractive_index);

        Color getColor () const;
        double getRefractiveIndex () const;

        /**
         * @brief Generates a refracted ray.
         *
         * @param hit
         * @return Ray
         */
        Ray scatter (const Hit& hit) const;
};

#endif
