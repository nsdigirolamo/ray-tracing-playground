#include <list>
#include <memory>

#include "camera.hpp"
#include "intersectables/intersectable.hpp"
#include "intersectables/plane.hpp"
#include "intersectables/sphere.hpp"
#include "materials/diffuse.hpp"
#include "materials/metallic.hpp"
#include "primitives/vector.hpp"

int main () {

    Camera camera {
        {{0, 0, 0}},
        1080,
        1920,
        90,
        0
    };

    Color pinkish = {{0.7, 0.3, 0.3}};
    Color greenish = {{0.3, 0.7, 0.3}};
    Color blueish = {{0.3, 0.3, 0.7}};
    Color yellowish = {{0.8, 0.8, 0.0}};

    Sphere metal_sphere_1 {
        {{-1.0, 0, 2.0}},
        0.5,
        std::make_unique<Metallic>(greenish, 1)
    };

    Sphere metal_sphere_2 = {
        {{0, 0, 2.0}},
        0.5,
        std::make_unique<Metallic>(pinkish, 0.5)
    };

    Sphere metal_sphere_3 = {
        {{1.0, 0, 2.0}},
        0.5,
        std::make_unique<Metallic>(blueish, 0)
    };

    Plane diffuse_plane = {
        {{0, -0.5, 0}},
        {{0, 1, 0}},
        std::make_unique<Diffuse>(yellowish)
    };

    std::list<Intersectable*> objects = {
        &metal_sphere_1,
        &metal_sphere_2,
        &metal_sphere_3,
        &diffuse_plane
    };

    std::vector<Color> pixels = camera.capture(objects, 100, 50);
    writeImage("scene", pixels, camera.getImageHeight(), camera.getImageWidth());
}