#include "random_utils.hpp"

Point generateRandomPointInUnitSphere () {

    std::random_device generator;
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    double x, y, z;
    Point point;

    do {

        x = distribution(generator);
        y = distribution(generator);
        z = distribution(generator);

        point = {{x, y, z}};

    } while (1 < length(point));

    return point;
}

Point generateRandomPointInUnitHemisphere (const Vector<3>& normal) {

    Point in_sphere = generateRandomPointInUnitSphere();
    return dot(normal, in_sphere) > 0 ? in_sphere : -1 * in_sphere;
}