#include "camera.hpp"
#include "sphere.hpp"

int main () {

    Camera camera;

    Point sphere_location = {{0, 0, 2.0}};
    double radius = 0.5;
    Sphere sphere = {sphere_location, radius};

    camera.capture(sphere, "sphere");
}