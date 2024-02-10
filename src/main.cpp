#include <list>
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
        {{0, 0, 0}},
        1080,
        1920,
        90,
        2.0,
        0.0,
        {{0, 0, 2.0}}
    };

    Sphere refractive1 = {
        {{0, 0, 2.0}},
        0.5,
        std::make_unique<Refractive>(WHITE, 1.5)
    };

    Sphere diffuse1 = {
        {{-2.0, 0, 9.0}},
        0.5,
        std::make_unique<Diffuse>(RED)
    };

    Sphere diffuse2 = {
        {{0, 0, 9.0}},
        0.5,
        std::make_unique<Diffuse>(GREEN)
    };

    Sphere diffuse3 = {
        {{2.0, 0, 9.0}},
        0.5,
        std::make_unique<Diffuse>(BLUE)
    };

    Plane diffuse_plane = {
        {{0, -0.5, 0}},
        {{0, 1, 0}},
        std::make_unique<Diffuse>(CORAL)
    };

    std::list<Intersectable*> objects = {
        &refractive1,
        &diffuse1,
        &diffuse2,
        &diffuse3,
        &diffuse_plane
    };

    std::vector<Color> pixels = camera.capture(objects, 50, 100);
    writeImage("scene", pixels, camera.getImageHeight(), camera.getImageWidth());
}