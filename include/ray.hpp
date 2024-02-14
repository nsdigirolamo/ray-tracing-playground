#ifndef RAY_HPP
#define RAY_HPP

#include "primitives/unit_vector.hpp"
#include "primitives/vector.hpp"

class Ray {

    public:

    const Point origin;
    const UnitVector<3> direction;
};

#endif