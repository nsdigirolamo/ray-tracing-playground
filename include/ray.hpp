#ifndef RAY_HPP
#define RAY_HPP

#include "point.hpp"

class Ray {

    public:

    Point origin;
    Vector<3> direction;

    Ray (const Point& origin, const Vector<3>& direction) {
        this->origin = origin;
        this->direction = unit(direction);
    }
};

#endif