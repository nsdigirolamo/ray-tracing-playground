#ifndef HIT_HPP
#define HIT_HPP

#include "ray.hpp"

class Hit {

    public:

    const double distance;
    const Ray surface_normal;
};

#endif