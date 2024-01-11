#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <list>

#include "matrix.hpp"
#include "point.hpp"
#include "vector.hpp"

class Intersectable;
class Sphere;

class Camera {

    private:

    int image_height;
    int image_width;

    double vertical_fov;
    double horizontal_fov;

    double view_height;
    double view_width;
    double focal_length;

    public:

    Point location;

    Matrix<3, 3> rotation_matrix;

    Camera ();

    Camera (
        const Point &location,
        const int image_height,
        const int image_width,
        const double horizontal_fov,
        const double yaw
    );

    Camera (
        const Point &location,
        const int image_height,
        const int image_width,
        const double vertical_fov,
        const double horizontal_fov,
        const double yaw
    );

    int getImageHeight () const;
    int getImageWidth () const;

    double getVerticalFOV () const;
    double getHorizontalFOV () const;

    double getViewHeight () const;
    double getViewWidth () const;
    double getFocalLength () const;

    void capture (const std::list<Intersectable*> objects, const std::string file_name) const;
};

#endif