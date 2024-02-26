#include "intersectables/sphere.hpp"

Sphere::Sphere (const Point& origin, double radius, std::unique_ptr<Material> material)
    : origin(origin)
    , radius(radius)
    , material(std::move(material))
{ }

std::optional<Hit> Sphere::intersects(const Ray& ray) const {

    UnitVector<3> ud = ray.direction;
    Vector<3> oc = ray.origin - this->origin;

    double discriminant = pow(dot(ud, oc), 2) - (oc.length_squared() - pow(this->radius, 2));

    if (0 <= discriminant) {

        double uoc = -1 * dot(ray.direction, (Vector<3>)(ray.origin - this->origin));

        double distance;

        double smaller_distance = uoc - sqrt(discriminant);
        double larger_distance = uoc + sqrt(discriminant);

        if (MINIMUM_INTERSECT_DISTANCE < smaller_distance) {
            distance = smaller_distance;
        } else if (MINIMUM_INTERSECT_DISTANCE < larger_distance) {
            distance = larger_distance;
        } else {
            return {};
        }

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
