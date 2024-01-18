#ifndef RAY_HPP
#define RAY_HPP

#include "primitives/vector.hpp"

class Ray {

    public:

    const Point origin;
    const Vector<3> direction;

    Ray (const Point& origin, const Vector<3>& direction);
};

#endif