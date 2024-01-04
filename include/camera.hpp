#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "point.hpp"
#include "sphere.hpp"
#include "vector.hpp"

class Camera {

    private:

    double vertical_fov;
    double horizontal_fov;

    double view_height;
    double view_width;
    double focal_length;

    public:

    Point location;

    int image_height;
    int image_width;

    Matrix<3, 3> rotation_matrix;

    Camera ();

    Camera (
        const Point location,
        const int image_height,
        const int image_width,
        const double horizontal_fov,
        const double yaw
    );

    Camera (
        const Point location,
        const int image_height,
        const int image_width,
        const double vertical_fov,
        const double horizontal_fov,
        const double yaw
    );

    void capture (const Sphere& sphere, const std::string file_name) const;
};

#endif