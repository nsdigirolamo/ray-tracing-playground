#include "ray.hpp"

Ray::Ray (const Point& origin, const Vector<3>& direction) {
    this->origin = origin;
    this->direction = unit(direction);
}
