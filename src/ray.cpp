#include "ray.hpp"

Ray::Ray (
    const Point& origin,
    const UnitVector<3>& direction
)
    : origin(origin)
    , direction(direction)
{ }
