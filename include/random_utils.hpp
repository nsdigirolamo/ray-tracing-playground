#ifndef RANDOM_UTILS_HPP
#define RANDOM_UTILS_HPP

#include <random>

#include "primitives/vector.hpp"

/**
 * @brief Generates a uniformly random double between -1 and 1.
 *
 * @return double
 */
double randomDouble ();

/**
 * @brief Generates a random point in a unit sphere.
 *
 * @return Vector<3>
 */
Vector<3> randomInUnitSphere ();

/**
 * @brief Generates a random point on the surface of a unit sphere.
 *
 * @return UnitVector<3>
 */
UnitVector<3> randomOnUnitSphere ();

/**
 * @brief Generates a random point in a hemisphere of a unit sphere.
 *
 * @param normal The normal that defines the hemisphere.
 * @return Vector<3>
 */
Vector<3> randomInUnitHemisphere (const UnitVector<3>& normal);

/**
 * @brief Generates a random point on the surface of a hemisphere of a unit sphere.
 *
 * @param normal The normal that defines the hemisphere.
 * @return UnitVector<3>
 */
UnitVector<3> randomOnUnitHemisphere (const UnitVector<3>& normal);

/**
 * @brief Generates a random point in a unit circle.
 *
 * @return Vector<2>
 */
Vector<2> randomInUnitCircle ();

/**
 * @brief Generates a random point on the perimeter of a unit circle.
 *
 * @return UnitVector<2>
 */
UnitVector<2> randomOnUnitCircle ();

#endif