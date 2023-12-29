#include <fstream>

#include "camera.hpp"

Camera::Camera (
    const Point origin,
    // const Vector<3> direction,
    const double focal_length,
    const double view_height,
    const double view_width,
    const int image_height
) {
    this->origin = origin;
    // this->direction = direction;

    this->focal_length = focal_length;
    this->view_height = view_height;
    this->view_width = view_width;
    this->view_ratio = this->view_width / this->view_height;

    this->image_height = image_height;
    this->image_width = this->image_height * this->view_ratio;
    this->pixel_height_distance = this->view_height / this->image_height;
    this->pixel_width_distance = this->view_width / this->image_width;
}

Camera::Camera () {
    *this = {
        {{0, 0, 0}}, // origin
        // {{1, 0, 0}}, // direction
        1.0, // focal_length
        1.0, // view_height
        2.0, // view_width
        100 // image_height
    };
}

void Camera::capture (const Sphere& sphere, const std::string file_name) const {

    Color* pixels = new Color[image_width * image_height];

    for (int row = 0; row < image_height; row++) {
        for (int col = 0; col < image_width; col++) {

            Vector<3> direction {{
                (col * this->pixel_width_distance) - (this->view_width / 2),
                (row * this->pixel_height_distance) - (this->view_height / 2),
                this->focal_length
            }};

            const Ray ray = {this->origin, direction};

            if (sphere.intersects(ray)) {
                pixels[(row * this->image_width) + col] = {{255, 0, 0}};
            } else {
                pixels[(row * this->image_width) + col] = {{0, 0, 0}};
            }
        }
    }

    std::ofstream file(file_name + ".ppm");
    file << "P3\n" << image_width << " " << image_height << "\n" << "255\n";

    for (int row = 0; row < image_height; row++) {
        for (int col = 0; col < image_width; col++) {
            Color pixel = pixels[(row * this->image_width) + col];
            file << pixel[0] << " " << pixel[1] << " " << pixel[2] << "\n";
        }
    }

    delete [] pixels;
}