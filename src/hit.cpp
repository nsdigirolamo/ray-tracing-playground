#include "hit.hpp"

Hit::Hit (
    const Point &location, 
    const Vector<3> &normal, 
    const double distance, 
    const Color &color
)
    : location(location)
    , normal(unit(normal))
    , distance(distance)
    , color(color)
{ }