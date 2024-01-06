#ifndef HIT_HPP
#define HIT_HPP

#include "color.hpp"
#include "point.hpp"
#include "ray.hpp"

class Hit {

    public:

    Point location;
    Ray normal;
    Color color;
};

#endif