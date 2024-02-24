#ifndef HIT_HPP
#define HIT_HPP

#include "ray.hpp"

/**
 * @brief A utility class for storing information about ray intersections.
 */
class Hit {

    public:

    const UnitVector<3> incoming; /** The ray that caused the hit. */
    const double distance; /** The distance along the incoming ray where the hit occurred. */
    const Ray surface_normal; /** The surface normal of the surface that was hit. */
    const bool is_front; /** Whether or not the hit occurred on the front of the surface. */
};

#endif