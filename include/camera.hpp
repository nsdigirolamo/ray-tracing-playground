#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <list>
#include <optional>
#include <ostream>
#include <vector>

#include "intersectables/intersectable.hpp"
#include "primitives/color.hpp"
#include "primitives/vector.hpp"
#include "random_utils.hpp"
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
        double focal_radius;

        double pixel_height;
        double pixel_width;

        UnitVector<3> up_direction;
        UnitVector<3> view_direction;
        UnitVector<3> view_vert;
        UnitVector<3> view_horz;

        void helpConstruct (
            const Point& location,
            const int image_height,
            const int image_width,
            const double horizontal_fov,
            const double focal_length,
            const double focal_angle,
            const Point& looking_at,
            const UnitVector<3>& up_direction
        );

    public:

        Camera (
            const Point& location,
            const int image_height,
            const int image_width,
            const double horizontal_fov,
            const double vertical_fov,
            const double focal_length,
            const double focal_angle,
            const Point& looking_at,
            const UnitVector<3>& up_direction
        );

        Camera (
            const Point& location,
            const int image_height,
            const int image_width,
            const double horizontal_fov,
            const double focal_length,
            const double focal_angle,
            const Point& looking_at,
            const UnitVector<3>& up_direction
        );

        Camera (
            const Point& location,
            const int image_height,
            const int image_width,
            const double horizontal_fov,
            const double focal_length,
            const double focal_angle,
            const Point& looking_at
        );

        Camera (
            const Point& location,
            const int image_height,
            const int image_width,
            const double horizontal_fov,
            const double focal_length,
            const Point& looking_at
        );

        Camera (
            const Point& location,
            const int image_height,
            const int image_width,
            const double horizontal_fov,
            const Point& looking_at
        );

        Point getLocation () const;

        int getImageHeight () const;
        int getImageWidth () const;

        double getVerticalFOV () const;
        double getHorizontalFOV () const;

        double getViewHeight () const;
        double getViewWidth () const;
        double getFocalLength () const;

        double getPixelHeight () const;
        double getPixelWidth () const;

        Ray generate_ray (const int x, const int y) const;
        std::vector<Color> capture (const std::list<Intersectable*> scene, const int samples_per_pixel, const int steps_per_sample) const;
};

Color trace (const Ray& ray, const std::list<Intersectable*> intersectables, const int steps);

#endif