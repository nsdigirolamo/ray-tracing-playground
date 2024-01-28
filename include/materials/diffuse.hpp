#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "hit.hpp"
#include "materials/material.hpp"
#include "primitives/color.hpp"
#include "random_utils.hpp"
#include "ray.hpp"

class Diffuse : public Material {

    private:

        const Color color;

    public:

        Diffuse (const Color& color);

        Color getColor () const;
        Ray scatter (const Hit& hit) const;
};

#endif
