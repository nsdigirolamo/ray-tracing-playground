#include "random_utils.hpp"

std::random_device generator;
std::uniform_real_distribution<double> distribution(-1.0, 1.0);

double randomDouble () {
    return distribution(generator);
}

Point randomPointInUnitSphere () {

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

Point randomPointInUnitHemisphere (const Vector<3>& normal) {

    Point in_sphere = randomPointInUnitSphere();
    return dot(normal, in_sphere) > 0 ? in_sphere : -1 * in_sphere;
}

Vector<2> randomPointInUnitCircle () {

    double x, y;
    Vector<2> point;

    do {

        x = randomDouble();
        y = randomDouble();

        point = {{x, y}};

    } while (1 < length(point));

    return point;
}