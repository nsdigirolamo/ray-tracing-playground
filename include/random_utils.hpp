#ifndef RANDOM_UTILS_HPPS
#define RANDOM_UTILS_HPP

#include <random>

#include "primitives/vector.hpp"

Point generateRandomPointInUnitSphere ();
Point generateRandomPointInUnitHemisphere (const Vector<3>& normal);

#endif