#include "intersectables/sphere.hpp"

Sphere::Sphere (const Point& origin, double radius, std::unique_ptr<Material> material)
    : origin(origin)
    , radius(radius)
    , material(std::move(material))
{ }

std::optional<Hit> Sphere::intersects(const Ray& ray) const {

    UnitVector<3> ud = ray.direction;
    Vector<3> oc = ray.origin - this->origin;

    double discriminant = pow(dot(ud, oc), 2) - (length_squared(oc) - pow(this->radius, 2));

    if (0 <= discriminant) {

        double uoc = -1 * dot(ray.direction, (Vector<3>)(ray.origin - this->origin));
        double distance = uoc - sqrt(discriminant);
        distance = distance < 0 ? uoc + sqrt(discriminant) : distance;

        if (distance < MINIMUM_INTERSECT_DISTANCE) { return {}; }

        Point intersection = ray.origin + ray.direction * distance;
        UnitVector<3> normal_direction = intersection - this->origin;
        bool is_front = dot(ray.direction, normal_direction) <= 0;

        Ray surface_normal = is_front ? (Ray){intersection, normal_direction} : (Ray){intersection, -1.0 * normal_direction};

        Hit hit = {
            ray.direction,
            distance,
            surface_normal,
            is_front
        };

        return hit;
    }

    return {};
}

const Material& Sphere::getMaterial () const {
    return *(this->material);
}
