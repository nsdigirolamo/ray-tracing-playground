#include "random_utils.hpp"

std::random_device generator;
std::uniform_real_distribution<double> distribution(-1.0, 1.0);

double randomDouble () {
    return distribution(generator);
}

Vector<3> randomInUnitSphere () {

    double x, y, z;
    Point point;

    do {

        x = randomDouble();
        y = randomDouble();
        z = randomDouble();

        point = {{x, y, z}};

    } while (1 < length(point));

    return point;
}

UnitVector<3> randomOnUnitSphere () {
    return (UnitVector<3>)(randomInUnitSphere());
}

Vector<3> randomInUnitHemisphere (const UnitVector<3>& normal) {
    Point in_sphere = randomInUnitSphere();
    return dot(normal, in_sphere) > 0 ? in_sphere : -1 * in_sphere;
}

UnitVector<3> randomPointOnUnitHemisphere (const UnitVector<3>& normal) {
    return (UnitVector<3>)(randomInUnitHemisphere(normal));
}

Vector<2> randomInUnitCircle () {

    double x, y;
    Vector<2> point;

    do {

        x = randomDouble();
        y = randomDouble();

        point = {{x, y}};

    } while (1 < length(point));

    return point;
}

UnitVector<2> randomOnUnitCircle () {
    return (UnitVector<2>)(randomInUnitCircle());
}