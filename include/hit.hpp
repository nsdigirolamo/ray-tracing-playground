#ifndef HIT_HPP
#define HIT_HPP

#include "color.hpp"
#include "point.hpp"
#include "vector.hpp"

class Hit {

    public:

    const Point location;
    const Vector<3> normal;
    const double distance;
    const Color color;

    Hit (const Point &location, const Vector<3> &normal, const double distance, const Color &color);
};

#endif