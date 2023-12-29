#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "point.hpp"
#include "sphere.hpp"
#include "vector.hpp"

class Camera {

    private:

    Point origin;
    // Vector<3> direction;

    double focal_length;
    double view_height;
    double view_width;
    double view_ratio;

    int image_height;
    int image_width;
    double pixel_height_distance;
    double pixel_width_distance;

    public:

    Camera ();
    Camera (
        const Point origin,
        // const Vector<3> direction,
        const double focal_length,
        const double viewport_width,
        const double viewport_height,
        const int image_height
    );

    void capture (const Sphere& sphere, const std::string file_name) const;
};

#endif