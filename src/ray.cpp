#include "ray.hpp"

Ray::Ray (
    const Point& origin,
    const Vector<3>& direction
)
    : origin(origin)
    , direction(unit(direction))
{ }
