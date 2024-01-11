#include <optional>
#include <fstream>

#include "camera.hpp"
#include "color.hpp"
#include "hit.hpp"
#include "intersectable.hpp"
#include "ray.hpp"
#include "sphere.hpp"

const Point default_location = {{0, 0, 0}};
constexpr int default_image_height = 1080;
constexpr int default_image_width = 1920;
constexpr double default_horizontal_fov = 90.0;
constexpr double default_yaw = 0.0;

double to_radians (double degrees) {
    return degrees * M_PI / 180;
}

double to_degrees (double radians) {
    return radians * 180 / M_PI;
}

Camera::Camera () {
    *this = {
        default_location,
        default_image_height,
        default_image_width,
        default_horizontal_fov,
        default_yaw
    };
}

Camera::Camera (
    const Point &location,
    const int image_height,
    const int image_width,
    const double horizontal_fov,
    const double yaw
)
    : location(location)
    , image_height(image_height)
    , image_width(image_width) 
    , horizontal_fov(horizontal_fov)
{
    double hfov = to_radians(horizontal_fov);

    this->view_width = 2 * sin(hfov / 2);
    this->view_height = this->view_width * image_height / image_width;
    this->focal_length = cos(hfov / 2);

    double vfov = atan((this->view_height / 2) / this->focal_length);

    this->vertical_fov = to_degrees(vfov) * 2;

    const double radians_yaw = to_radians(yaw);
    this->rotation_matrix = {{
        {       cos(radians_yaw), 0, sin(radians_yaw) },
        {                     0,  1,                0 },
        {-1.0 * sin(radians_yaw), 0, cos(radians_yaw) }
    }};
}

Camera::Camera (
    const Point &location,
    const int image_height,
    const int image_width,
    const double vertical_fov,
    const double horizontal_fov,
    const double yaw
) 
    : location(location)
    , image_height(image_height)
    , image_width(image_width)
    , vertical_fov(vertical_fov)
    , horizontal_fov(horizontal_fov) 
{
    double hfov = to_radians(horizontal_fov);
    double vfov = to_radians(vertical_fov);

    this->view_height = 2 * sin(vfov / 2);
    this->focal_length = cos(vfov / 2);
    this->view_width = 2 * this->focal_length * tan(hfov / 2);

    const double radians_yaw = to_radians(yaw);
    this->rotation_matrix = {{
        {       cos(radians_yaw), 0, sin(radians_yaw) },
        {                      0, 1,                0 },
        {-1.0 * sin(radians_yaw), 0, cos(radians_yaw) }
    }};
}

int Camera::getImageHeight () const {
    return this->image_height;
}

int Camera::getImageWidth () const {
    return this->image_width;
}

double Camera::getVerticalFOV () const {
    return this->vertical_fov;
}

double Camera::getHorizontalFOV () const {
    return this->horizontal_fov;
}

double Camera::getViewHeight () const {
    return this->view_height;
}

double Camera::getViewWidth () const {
    return this->view_width;
}

double Camera::getFocalLength () const {
    return this->focal_length;
}

void Camera::capture (const std::list<Intersectable*> objects, const std::string file_name) const {

    Color* pixels = new Color[this->image_width * this->image_height];

    const double pixel_height = this->view_height / this->image_height;
    const double pixel_width = this->view_width / this->image_width;

    for (int row = 0; row < this->image_height; ++row) {
        for (int col = 0; col < this->image_width; ++col) {

            Vector<3> view_ray {{
                (col * pixel_width) - (this->view_width / 2),
                (row * pixel_height) - (this->view_height / 2),
                this->focal_length
            }};

            Vector<3> ray_direction = this->rotation_matrix.transform(view_ray);

            const Ray ray = {this->location, ray_direction};

            double closest_hit = INFINITY;

            for (auto it = objects.begin(); it != objects.end(); ++it) {

                std::optional<Hit> hit = (*it)->intersects(ray);

                if (hit && hit.value().distance < closest_hit) {

                    pixels[(row * this->image_width) + col] = hit.value().color;
                    closest_hit = hit.value().distance;

                } else if (closest_hit == INFINITY) {

                    Color sky = {{
                        255.0 * row / this->image_height,
                        255,
                        255,
                    }};

                    pixels[(row * this->image_width) + col] = sky;
                }
            }
        }
    }

    std::ofstream file(file_name + ".ppm");

    file << "P3\n\n";

    file << "# VFOV: " << this->vertical_fov << "\n";
    file << "# HFOV: " << this->horizontal_fov << "\n";
    file << "# VHGT: " << this->view_height << "\n";
    file << "# VWID: " << this->view_width << "\n";
    file << "# FLNG: " << this->focal_length << "\n\n";

    file << this->image_width << " " << this->image_height << "\n" << "255\n";

    for (int row = this->image_height - 1; 0 <= row; --row) {
        for (int col = 0; col < this->image_width; ++col) {
            Color pixel = pixels[(row * this->image_width) + col];
            file << (int)(pixel[0]) << " " << (int)(pixel[1]) << " " << (int)(pixel[2]) << "\n";
        }
        std::cout << row << " lines remaining...\n";
    }

    delete [] pixels;
}