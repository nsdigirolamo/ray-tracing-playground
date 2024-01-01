#include "camera.hpp"

int main () {

    Camera camera {
        {{0, 0, 0}},
        1080,
        1920,
        60.0,
        90.0,
        20.0
    };

    Point sphere_location = {{0, 0, 2.0}};
    double radius = 0.5;
    Sphere sphere = {sphere_location, radius};

    camera.capture(sphere, "sphere");
}