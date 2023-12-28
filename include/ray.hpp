#ifndef RAY_HPP
#define RAY_HPP

#include "point.hpp"
#include "vector.hpp"

class Ray {

    public:

    Point origin;
    Vector<3> direction;

    Ray (const Point& origin, const Vector<3>& direction);
};

#endif