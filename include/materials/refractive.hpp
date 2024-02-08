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

class Refractive : public Material {

    private:

        const Color color;
        const double refractive_index;

    public:

        Refractive (const Color& color, const double refractive_index);

        Color getColor () const;
        double getRefractiveIndex () const;
        Ray scatter (const Hit& hit) const;
};

#endif
