#include <list>

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

    Color greenish = {{0.3, 0.7, 0.3}};
    Metallic greenish_metal = {greenish};

    Sphere metal_sphere = {
        {{-1.0, 0, 2.0}},
        0.5,
        greenish_metal
    };

    Color pinkish = {{0.7, 0.3, 0.3}};
    Diffuse pinkish_diffuse = {pinkish};

    Sphere diffuse_sphere = {
        {{0, 0, 2.0}},
        0.5,
        pinkish_diffuse
    };

    Color yellowish = {{0.8, 0.8, 0.0}};
    Diffuse yellowish_diffuse = {yellowish};

    Plane diffuse_plane = {
        {{0, -0.5, 0}},
        {{0, 1, 0}},
        yellowish_diffuse
    };

    std::list<Intersectable*> objects = {
        &metal_sphere,
        &diffuse_sphere,
        &diffuse_plane
    };

    std::vector<Color> pixels = camera.capture(objects, 100, 50);
    writeImage("scene", pixels, camera.getImageHeight(), camera.getImageWidth());
}