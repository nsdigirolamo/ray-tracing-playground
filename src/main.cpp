#include <list>

#include "camera.hpp"
#include "intersectable.hpp"
#include "plane.hpp"
#include "sphere.hpp"

int main () {

    Camera camera;

    Point sphere_location = {{0, 0, 2.0}};
    double radius = 0.5;
    Sphere sphere = {sphere_location, radius};

    Point plane_origin = {{0, -0.5, 0}};
    Vector<3> plane_normal = {{0, 1, 0}};
    Plane plane = {plane_origin, plane_normal};

    std::list<Intersectable*> objects = {&sphere, &plane};

    camera.capture(objects, "scene");
}