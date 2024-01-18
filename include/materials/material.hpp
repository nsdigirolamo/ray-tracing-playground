#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "hit.hpp"
#include "primitives/vector.hpp"
#include "ray.hpp"

class Material {

    public:

        virtual double getAbsorbance () const = 0;
        virtual Color getColor () const = 0;
        virtual Ray scatter (const Hit& hit) const = 0;
};

#endif
