#ifndef METALLIC_HPP
#define METALLIC_HPP

#include "hit.hpp"
#include "materials/material.hpp"
#include "primitives/color.hpp"
#include "ray.hpp"
#include "random_utils.hpp"

class Metallic : public Material {

    private:

        const Color color;
        const double blur;

    public:

        Metallic (const Color& color, const double blur);

        Color getColor () const;
        Ray scatter (const Hit& hit) const;
};

#endif
