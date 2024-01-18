#include <ostream>

#include "camera.hpp"

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
    const Point& location,
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
    const Point& location,
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

std::vector<Color> Camera::capture (const std::list<Intersectable*> scene, const int steps) const {

    std::cout << "Rendering image...\n";

    const double pixel_height = this->view_height / this->image_height;
    const double pixel_width = this->view_width / this->image_width;

    std::vector<Color> pixels (this->image_width * this->image_height);

    for (int row = this->image_height - 1; 0 <= row; --row) {
        for (int col = 0; col < this->image_width; ++col) {

            Vector<3> view_direction {{
                (col * pixel_width) - (this->view_width / 2),
                (row * pixel_height) - (this->view_height / 2),
                this->focal_length
            }};

            view_direction = this->rotation_matrix.transform(view_direction);

            Ray ray = {this->location, view_direction};

            pixels[(row * this->image_width) + col] = trace(ray, scene, steps);
        }
        std::cout << row << " lines remaining...\n";
    }

    std::cout << "Done rendering!\n";

    return pixels;
}

Color trace (const Ray& ray, const std::list<Intersectable*> intersectables, const int steps) {

    std::optional<Hit> closest_hit = {};
    const Material* material;

    for (auto it = intersectables.begin(); it != intersectables.end(); ++it) {

        std::optional<Hit> hit = (*it)->intersects(ray);

        bool hit_is_closest = hit && closest_hit && hit.value().distance < closest_hit.value().distance;

        if (hit && (!closest_hit || hit_is_closest)) {

            closest_hit.emplace(hit.value());
            material = (*it)->getMaterial();
        }
    }

    if (closest_hit) {

        Hit hit = closest_hit.value();

        double absorbance = material->getAbsorbance();
        Color color = material->getColor();

        int new_steps = steps - 1;

        /**

        // Not working right now...

        if (0 < steps) {
            return absorbance * trace(material->scatter(hit), intersectables, new_steps);
        }
        */

        return color;
    }

    Color sky = {{
        150,
        232,
        252
    }};

    return sky;
}

void outputImage (const std::string file_name, std::vector<Color> pixels, int image_height, int image_width) {

    std::cout  << "Printing image to file...\n";

    std::ofstream file(file_name + ".ppm");

    file << "P3\n\n" << image_width << " " << image_height << "\n" << "255\n";

    for (int row = image_height - 1; 0 <= row; --row) {
        for (int col = 0; col < image_width; ++col) {
            Color pixel = pixels[(row * image_width) + col];
            file << (int)(pixel[0]) << " " << (int)(pixel[1]) << " " << (int)(pixel[2]) << "\n";
        }
    }

    std::cout << "Done printing to file!\n";
}
