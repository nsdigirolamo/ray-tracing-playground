#include "intersectables/sphere.hpp"

const double minimum_distance = 0.0001;

Sphere::Sphere (const Point& origin, double radius, std::unique_ptr<Material> material)
    : origin(origin)
    , radius(radius)
    , material(std::move(material))
{ }

std::optional<Hit> Sphere::intersects(const Ray& ray) const {

    UnitVector<3> ud = ray.direction;
    Vector<3> oc = ray.origin - this->origin;

    double discriminant = pow(dot(ud, oc), 2) - (dot(oc, oc) - pow(this->radius, 2));

    if (0 <= discriminant) {

        double uoc = -1 * dot(ray.direction, (Vector<3>)(ray.origin - this->origin));
        double distance = uoc - sqrt(discriminant);

        if (distance < minimum_distance) { return {}; }

        Point intersection = ray.origin + ray.direction * distance;
        Ray surface_normal = {intersection, intersection - this->origin};
        Hit hit = {
            ray.direction,
            distance, 
            surface_normal,
            dot(ray.direction, surface_normal.direction) <= 0
        };

        return hit;
    }

    return {};
}

const Material& Sphere::getMaterial () const {
    return *(this->material);
}
