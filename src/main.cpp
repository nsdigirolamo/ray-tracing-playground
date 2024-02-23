#include <list>
#include <cmath>
#include <memory>

#include "camera.hpp"
#include "intersectables/intersectable.hpp"
#include "intersectables/plane.hpp"
#include "intersectables/sphere.hpp"
#include "materials/diffuse.hpp"
#include "materials/metallic.hpp"
#include "materials/refractive.hpp"
#include "primitives/vector.hpp"

std::shared_ptr<Sphere> getRandomSphere (const Point& origin) {

    double r = randomDouble();
    Color color {{ fabs(randomDouble()), fabs(randomDouble()), fabs(randomDouble()) }};

    std::shared_ptr<Sphere> sphere;

    if (r < 0.33) {

        sphere = std::make_shared<Sphere>(
            origin,
            0.2,
            std::make_unique<Diffuse>(color)
        );

    } else if (r < 0.66) {

        sphere = std::make_shared<Sphere>(
            origin,
            0.2,
            std::make_unique<Metallic>(color, fabs(randomDouble()))
        );

    } else {

        sphere = std::make_shared<Sphere>(
            origin,
            0.2,
            std::make_unique<Refractive>(color, 1.0 + randomDouble())
        );
    }

    return sphere;
}

int main () {

    Camera camera {
        {{13, 1.25, 5}},
        1080,
        1920,
        70,
        14,
        0.4,
        {{0, 1, 0}}
    };

    std::shared_ptr<Plane> ground = std::make_shared<Plane>(
        (Point){{0, 0, 0}},
        (Vector<3>){{0, 1, 0}},
        std::make_unique<Diffuse>(SLATEGRAY)
    );

    std::shared_ptr<Sphere> glass = std::make_shared<Sphere>(
        (Point){{0, 1, 0}},
        1.0,
        std::make_unique<Refractive>(WHITESMOKE, 1.5)
    );

    std::shared_ptr<Sphere> diffuse = std::make_shared<Sphere>(
        (Point){{-4, 1, 0}},
        1.0,
        std::make_unique<Diffuse>(STEELBLUE)
    );

    std::shared_ptr<Sphere> metal = std::make_shared<Sphere>(
        (Point){{4, 1, 0}},
        1.0,
        std::make_unique<Metallic>(SALMON, 0.0)
    );

    std::list<std::shared_ptr<Intersectable>> objects {
        ground,
        glass,
        diffuse,
        metal
    };

    for (int i = 0; i < 5; ++i) {

        for (int j = 0; j < 10; ++j) {
            objects.push_back(getRandomSphere(
                (Point){{4.0 - 2.0 * i, 0.2, 2.0 + j}}
            ));
        }

        for (int j = 0; j < 10; ++j) {
            objects.push_back(getRandomSphere(
                (Point){{4.0 - 2.0 * i, 0.2, -2.0 - j}}
            ));
        }
    }

    for (int i = 0; i < 24; ++i) {

        for (int j = 0; j < 10; ++j) {
            objects.push_back(getRandomSphere(
                (Point){{6.0 + j * 2, 0.2, -12.0 + i}}
            ));
        }

        for (int j = 0; j < 10; ++j) {
            objects.push_back(getRandomSphere(
                (Point){{-6.0 + j * -2, 0.2, 12.0 - i}}
            ));
        }
    }

    std::vector<Color> pixels = camera.capture(objects, 50, 50, true);
    writeImage("scene", pixels, camera.getImageHeight(), camera.getImageWidth());
}