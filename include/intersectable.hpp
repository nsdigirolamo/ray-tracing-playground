#ifndef INTERSECTABLE_HPP
#define INTERSECTABLE_HPP

#include <optional>

class Hit;
class Ray;

class Intersectable {

    public:

    virtual std::optional<Hit> intersects (const Ray &ray) const = 0;
};

#endif