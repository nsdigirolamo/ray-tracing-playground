#include <fstream>

#include "camera.hpp"

double to_radians (double degrees) {
    return degrees * M_PI / 180;
}

Camera::Camera () {
    *this = {
        {{0, 0, 0}},
        1080,
        1920,
        90.0,
        0.0
    };
}

Camera::Camera (
    const Point &location,
    const int image_height,
    const int image_width,
    const double horizontal_fov,
    const double yaw
) {

    this->location = location;

    this->image_height = image_height;
    this->image_width = image_width;

    this->horizontal_fov = horizontal_fov;

    this->view_width = 2 * sin(to_radians(horizontal_fov / 2));
    this->view_height = this->view_width * image_height / image_width;
    this->focal_length = cos(to_radians(horizontal_fov / 2));

    // TODO: Not getting calculated properly.

    this->vertical_fov = atan((this->view_height / 2) / this->focal_length);

    const double radians_yaw = to_radians(yaw);
    this->rotation_matrix = {{
        {       cos(radians_yaw), 0, sin(radians_yaw) },
        {                     0, 1,         0 },
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
) {

    this->location = location;

    this->image_height = image_height;
    this->image_width = image_width;

    this->vertical_fov = vertical_fov;
    this->horizontal_fov = horizontal_fov;

    this->view_height = 2 * sin(to_radians(vertical_fov / 2));
    this->focal_length = cos(to_radians(vertical_fov / 2));
    this->view_width = 2 * this->focal_length * tan(to_radians(horizontal_fov / 2));

    const double radians_yaw = to_radians(yaw);
    this->rotation_matrix = {{
        {       cos(radians_yaw), 0, sin(radians_yaw) },
        {                     0, 1,         0 },
        {-1.0 * sin(radians_yaw), 0, cos(radians_yaw) }
    }};
}

void Camera::capture (const Sphere &sphere, const std::string file_name) const {

    Color* pixels = new Color[this->image_width * this->image_height];

    const double pixel_height = this->view_height / this->image_height;
    const double pixel_width = this->view_width / this->image_width;

    for (int row = 0; row < this->image_height; row++) {
        for (int col = 0; col < this->image_width; col++) {

            Vector<3> view_ray {{
                (col * pixel_width) - (this->view_width / 2),
                (row * pixel_height) - (this->view_height / 2),
                this->focal_length
            }};

            Vector<3> ray_direction = this->rotation_matrix.transform(view_ray);

            const Ray ray = {this->location, ray_direction};

            pixels[(row * this->image_width) + col] = sphere.intersects(ray);
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

    for (int row = 0; row < this->image_height; row++) {
        for (int col = 0; col < this->image_width; col++) {
            Color pixel = pixels[(row * this->image_width) + col];
            file << pixel[0] << " " << pixel[1] << " " << pixel[2] << "\n";
        }
        std::cout << this->image_height - row << " lines remaining...\n";
    }

    delete [] pixels;
}