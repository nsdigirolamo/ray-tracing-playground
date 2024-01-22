#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <fstream>
#include <list>
#include <optional>
#include <vector>

#include "hit.hpp"
#include "intersectables/intersectable.hpp"
#include "primitives/matrix.hpp"
#include "primitives/vector.hpp"
#include "ray.hpp"

class Camera {

    private:

        Point location;

        int image_height;
        int image_width;

        double vertical_fov;
        double horizontal_fov;

        double view_height;
        double view_width;
        double focal_length;

        Matrix<3, 3> rotation_matrix;

    public:

        Camera ();

        Camera (
            const Point& location,
            const int image_height,
            const int image_width,
            const double horizontal_fov,
            const double yaw
        );

        Camera (
            const Point& location,
            const int image_height,
            const int image_width,
            const double vertical_fov,
            const double horizontal_fov,
            const double yaw
        );

        Point getLocation () const;

        int getImageHeight () const;
        int getImageWidth () const;

        double getVerticalFOV () const;
        double getHorizontalFOV () const;

        double getViewHeight () const;
        double getViewWidth () const;
        double getFocalLength () const;

        Matrix<3, 3> getRotationMatrix () const;

        std::vector<Color> capture (const std::list<Intersectable*> scene, const int steps) const;
};

Color trace (const Ray& ray, const std::list<Intersectable*> intersectables, const int steps);
void outputImage (const std::string file_name, std::vector<Color> pixels, int image_height, int image_width);

#endif