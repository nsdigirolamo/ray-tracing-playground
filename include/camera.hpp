#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <list>
#include <memory>
#include <optional>
#include <ostream>
#include <vector>

#include "intersectables/intersectable.hpp"
#include "primitives/color.hpp"
#include "primitives/unit_vector.hpp"
#include "primitives/vector.hpp"
#include "random_utils.hpp"
#include "ray.hpp"

/**
 * @brief A utility class for executing the ray tracer and for generating images.
 */
class Camera {

    private:

        Point location; /** The camera's location in the scene. */

        int image_height; /** The height of the camera's image in pixels. */
        int image_width; /** The width of the camera's image in pixels. */

        double vertical_fov; /** The camera's vertical field of view. */
        double horizontal_fov; /** The camera's horizontal field of view. */

        double view_height; /** The hieght of the camera's view plane in the scene. */
        double view_width; /** The width of the camera's view plane in the scene. */
        double focal_distance; /** The distance from the camera location to the view plane. */
        double focal_radius; /** The radius of the camera's defocus disk. */

        double pixel_height; /** The height of a pixel on the view plane. */
        double pixel_width; /** The width of a pixel on the view plane. */

        UnitVector<3> up_direction; /** The camera's relative up direction. */
        UnitVector<3> view_direction; /** The direction the camera is pointing. */
        UnitVector<3> view_vertical; /** The direction from the center to the top of the view plane. */
        UnitVector<3> view_horizontal; /** The direction from the center to the left of the view plane. */

        /**
         * @brief A helper function that initializes camera member fields.
         *
         * @param location The camera location in space.
         * @param image_height The height of the image in pixels.
         * @param image_width The width of the image in pixels.
         * @param horizontal_fov The horizontal field of view in degrees.
         * @param focal_distance The distance between the camera's location and its point of focus.
         * @param focal_angle The maximum angle a ray can diverge from its point of focus.
         * @param looking_at The point in space the camera is directed towards.
         * @param up_direction The relative up direction of the camera.
         */
        void helpConstruct (
            const Point& location,
            const int image_height,
            const int image_width,
            const double horizontal_fov,
            const double focal_distance,
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
        double getFocalDistance () const;
        double getFocalRadius () const;

        double getPixelHeight () const;
        double getPixelWidth () const;

        UnitVector<3> getUpDirection () const;
        UnitVector<3> getViewDirection () const;
        UnitVector<3> getViewVertical () const;
        UnitVector<3> getViewHorizontal () const;

        /**
         * @brief Generates a point in space for an initial ray to be projected
         * from the camera.
         *
         * @return Point
         */
        Point generateRayOrigin () const;

        /**
         * @brief Calculates a given pixel's location in the scene.
         *
         * @param row The pixel's row in the image.
         * @param col The pixel's column in the image.
         * @param is_anti_aliased Whether or not the image is anti aliased.
         * @return Point
         */
        Point calculatePixelLocation (
            const int row, const int col,
            const bool is_anti_aliased
        ) const;

        /**
         * @brief Gets an initial ray for a given pixel.
         *
         * @param row The pixel's row in the image.
         * @param col The pixel's column in the image.
         * @param is_anti_aliased Whether or not the image is anti aliased.
         * @return Ray
         */
        Ray getRay (
            const int row,
            const int col,
            const bool is_anti_aliased
        ) const;

        /**
         * @brief Begins the ray tracing process by projecting a given number of
         * initial rays.
         *
         * @param scene A list of objects in the scene.
         * @param samples_per_pixel The number of rays to project per pixel.
         * @param steps_per_sample The maximum recursion depth for each ray.
         * @param is_anti_aliased Whether or not the image is anti aliased.
         * @return std::vector<Color> A vector of colors that correspond to the
         * pixels in a rendered image.
         */
        std::vector<Color> capture (
            const std::list<std::shared_ptr<Intersectable>> scene,
            const int samples_per_pixel,
            const int steps_per_sample,
            const bool is_anti_aliased
        ) const;
};

/**
 * @brief Traces a given ray's path through the scene and determines its
 * resulting Color.
 *
 * @param ray The ray to trace.
 * @param intersectables The objects in the scene.
 * @param steps The maximum recursion depth of the function.
 * @return Color
 */
Color trace (const Ray& ray, const std::list<std::shared_ptr<Intersectable>> intersectables, const int steps);

#endif