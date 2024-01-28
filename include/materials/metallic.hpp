#ifndef METALLIC_HPP
#define METALLIC_HPP

#include "hit.hpp"
#include "materials/material.hpp"
#include "primitives/color.hpp"
#include "ray.hpp"

class Metallic : public Material {

    private:

        const Color color;

    public:

        Metallic (const Color& color);

        Color getColor () const;
        Ray scatter (const Hit& hit) const;
};

#endif
