#ifndef RAY_HPP
#define RAY_HPP

#include "primitives/vector.hpp"

class Ray {

    public:

    const Point origin; /** The ray's location in the scene. */
    const UnitVector<3> direction; /** The ray's direction from its origin. */
};

#endif