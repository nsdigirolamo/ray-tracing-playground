#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "hit.hpp"
#include "materials/material.hpp"
#include "primitives/vector.hpp"
#include "random_utils.hpp"
#include "ray.hpp"

class Diffuse : public Material {

    private:

        const double absorbance;
        const Color color;

    public:

        Diffuse (const double absorbance, const Color& color);

        double getAbsorbance () const;
        Color getColor () const;
        Ray scatter (const Hit& hit) const;
};

#endif
