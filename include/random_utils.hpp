#ifndef RANDOM_UTILS_HPPS
#define RANDOM_UTILS_HPP

#include <random>

#include "primitives/vector.hpp"

double randomDouble ();

Point randomPointInUnitSphere ();
Point randomPointOnUnitSphere ();

Point randomPointInUnitHemisphere (const Vector<3>& normal);
Point randomPointOnUnitHemisphere (const Vector<3>& normal);

Vector<2> randomPointInUnitCircle ();
Vector<2> randomPointOnUnitCircle ();

#endif