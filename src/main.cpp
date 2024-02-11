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
        10.0,
        10.0,
        {{0, 0, 10}}
    };

    Sphere diffuse1 = {
        {{5, 0, 5}},
        1.0,
        std::make_unique<Diffuse>(RED)
    };

    Sphere diffuse2 = {
        {{0, 0, 10}},
        1.0,
        std::make_unique<Diffuse>(GREEN)
    };

    Sphere diffuse3 = {
        {{-5, 0, 15}},
        1.0,
        std::make_unique<Diffuse>(BLUE)
    };

    Sphere diffuse4 = {
        {{-10, 0, 20}},
        1.0,
        std::make_unique<Diffuse>(YELLOW)
    };

    Sphere diffuse5 = {
        {{-15, 0, 25}},
        1.0,
        std::make_unique<Diffuse>(MAGENTA)
    };

    Sphere diffuse6 = {
        {{-20, 0, 30}},
        1.0,
        std::make_unique<Diffuse>(CYAN)
    };

    Sphere diffuse7 = {
        {{-25, 0, 35}},
        1.0,
        std::make_unique<Diffuse>(MAGENTA)
    };

    Plane diffuse_plane = {
        {{0, -1.0, 0}},
        {{0, 1, 0}},
        std::make_unique<Diffuse>(CORAL)
    };

    std::list<Intersectable*> objects = {
        &diffuse1,
        &diffuse2,
        &diffuse3,
        &diffuse4,
        &diffuse5,
        &diffuse6,
        &diffuse7,
        &diffuse_plane
    };

    std::vector<Color> pixels = camera.capture(objects, 100, 100);
    writeImage("scene", pixels, camera.getImageHeight(), camera.getImageWidth());
}