#ifndef HIT_HPP
#define HIT_HPP

#include "ray.hpp"

class Hit {

    public:

    const Vector<3> incoming;
    const double distance;
    const Ray surface_normal;
};

#endif