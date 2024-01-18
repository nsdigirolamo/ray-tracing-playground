#include <list>

#include "camera.hpp"
#include "intersectables/intersectable.hpp"
#include "intersectables/plane.hpp"
#include "intersectables/sphere.hpp"
#include "materials/diffuse.hpp"
#include "primitives/vector.hpp"

int main () {

    Camera camera;

    Point sphere_origin = {{0, 0, 2.0}};
    double sphere_radius = 0.5;
    Color sphere_color = {{255, 0, 0}};
    double sphere_absorbance = 0.5;
    Diffuse sphere_material = {sphere_absorbance, sphere_color};
    Sphere sphere = {sphere_origin, sphere_radius, sphere_material};

    Point plane_origin = {{0, -0.5, 0}};
    Vector<3> plane_normal = {{0, 1, 0}};
    Color plane_color = {{0, 255, 0}};
    double plane_absorbance = 0.5;
    Diffuse plane_material = {plane_absorbance, plane_color};
    Plane plane = {plane_origin, plane_normal, plane_material};

    std::list<Intersectable*> objects = {&sphere, &plane};

    std::vector<Color> pixels = camera.capture(objects, 1);
    outputImage("scene", pixels, 1080, 1920);
}