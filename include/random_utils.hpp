#ifndef RANDOM_UTILS_HPP
#define RANDOM_UTILS_HPP

#include <random>

#include "primitives/unit_vector.hpp"
#include "primitives/vector.hpp"

double randomDouble ();

Vector<3> randomInUnitSphere ();
UnitVector<3> randomOnUnitSphere ();

Vector<3> randomInUnitHemisphere (const UnitVector<3>& normal);
UnitVector<3> randomOnUnitHemisphere (const UnitVector<3>& normal);

Vector<2> randomInUnitCircle ();
UnitVector<2> randomOnUnitCircle ();

#endif