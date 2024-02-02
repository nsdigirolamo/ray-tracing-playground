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

    this->pixel_height = this->view_height / this->image_height;
    this->pixel_width = this->view_width / this->image_width;

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

    this->pixel_height = this->view_height / this->image_height;
    this->pixel_width = this->view_width / this->image_width;

    const double radians_yaw = to_radians(yaw);
    this->rotation_matrix = {{
        {       cos(radians_yaw), 0, sin(radians_yaw) },
        {                      0, 1,                0 },
        {-1.0 * sin(radians_yaw), 0, cos(radians_yaw) }
    }};
}

Point Camera::getLocation () const {
    return this->location;
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

double Camera::getPixelHeight () const {
    return this->pixel_height;
}

double Camera::getPixelWidth () const {
    return this->pixel_width;
}

Matrix<3, 3> Camera::getRotationMatrix () const {
    return this->rotation_matrix;
}

Ray Camera::generate_ray (const int row, const int col) const {

    double x_position = col * pixel_width;
    double y_position = row * pixel_height;

    Vector<2> offset = randomPointInUnitCircle();
    double sample_x_offset = offset[0] * pixel_width;
    double sample_y_offset = offset[1] * pixel_height;

    double global_x_offset = this->view_width / 2;
    double global_y_offset = this->view_height / 2;

    Vector<3> view_direction {{
        x_position + sample_x_offset - global_x_offset,
        y_position + sample_y_offset - global_y_offset,
        this->focal_length
    }};

    view_direction = this->rotation_matrix.transform(view_direction);

    return {
        this->location,
        view_direction
    };
}

std::vector<Color> Camera::capture (const std::list<Intersectable*> scene, const int samples_per_pixel, const int steps_per_sample) const {

    std::cout << "Rendering image...\n";

    const double pixel_height = this->view_height / this->image_height;
    const double pixel_width = this->view_width / this->image_width;

    std::vector<Color> pixels (this->image_width * this->image_height);

    for (int row = this->image_height - 1; 0 <= row; --row) {
        for (int col = 0; col < this->image_width; ++col) {

            Color color = {{0, 0, 0}};

            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                Ray ray = this->generate_ray(row, col);
                color += trace(ray, scene, steps_per_sample);
            }

            pixels[(row * this->image_width) + col] = color / samples_per_pixel;
        }
        std::cout << row << " lines remaining...\n";
    }

    std::cout << "Done rendering!\n";

    return pixels;
}

Color trace (const Ray& ray, const std::list<Intersectable*> intersectables, int steps) {

    std::optional<std::tuple<Intersectable*, Hit>> closest = {};

    for (auto it = intersectables.begin(); it != intersectables.end(); ++it) {

        std::optional<Hit> hit = (*it)->intersects(ray);

        bool hit_is_closest = \
            hit.has_value() && \
            closest.has_value() && \
            hit.value().distance < std::get<Hit>(closest.value()).distance;

        if (hit.has_value() && (!closest.has_value() || hit_is_closest)) {
            closest.emplace(*it, hit.value());
        }
    }

    if (closest.has_value()) {

        Hit hit = std::get<Hit>(closest.value());
        Intersectable* intersectable = std::get<Intersectable*>(closest.value());
        const Material& material = intersectable->getMaterial();

        Color material_color = material.getColor();
        Color traced_color = trace(material.scatter(hit), intersectables, steps);

        --steps;

        return 0 < steps ? hadamard(material_color, traced_color) : material_color;
    }

    Color sky = {{
        0.60,
        0.90,
        1.0
    }};

    return sky;
}
