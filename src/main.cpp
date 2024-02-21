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

int main () {

    Camera camera {
        {{13, 2, 3}},
        1080,
        1920,
        70,
        10.0,
        0.6,
        {{0, 0, 0}}
    };

    std::shared_ptr<Sphere> ground = std::make_shared<Sphere>(
        (Point){{0, -1000, 0}},
        1000,
        std::make_unique<Diffuse>((Color){0.5, 0.5, 0.5})
    );

    std::shared_ptr<Sphere> glass = std::make_shared<Sphere>(
        (Point){{0, 1, 0}},
        1.0,
        std::make_unique<Refractive>(WHITESMOKE, 1.5)
    );

    std::shared_ptr<Sphere> diffuse = std::make_shared<Sphere>(
        (Point){{-4, 1, 0}},
        1.0,
        std::make_unique<Diffuse>((Color){0.4, 0.2, 0.1})
    );

    std::shared_ptr<Sphere> metal = std::make_shared<Sphere>(
        (Point){{4, 1, 0}},
        1.0,
        std::make_unique<Metallic>((Color){0.7, 0.6, 0.5}, 0.0)
    );

    std::list<std::shared_ptr<Intersectable>> objects = {
        ground,
        glass,
        diffuse,
        metal
    };

    for (int i = -11; i < 11; ++i) {
        for (int j = -11; j < 11; ++j) {

            double get_material = randomDouble();
            Point center {{ i + 0.9 * randomDouble(), 0.2, j + 0.9 * randomDouble() }};
            Color color {{ fabs(randomDouble()), fabs(randomDouble()), fabs(randomDouble()) }};
            std::shared_ptr<Sphere> sphere;

            if (get_material < 0.33) {

                sphere = std::make_shared<Sphere>(
                    center,
                    0.2,
                    std::make_unique<Diffuse>(color)
                );

            } else if (get_material < 0.66) {

                sphere = std::make_shared<Sphere>(
                    center,
                    0.2,
                    std::make_unique<Metallic>(color, fabs(randomDouble()))
                );

            } else {

                sphere = std::make_shared<Sphere>(
                    center,
                    0.2,
                    std::make_unique<Refractive>(color, 1.0 + randomDouble())
                );
            }

            objects.push_back(sphere);
        }
    }

    std::vector<Color> pixels = camera.capture(objects, 500, 50, true);
    writeImage("scene", pixels, camera.getImageHeight(), camera.getImageWidth());
}