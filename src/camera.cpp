#include "camera.hpp"

#define to_radians(degrees) ((double)(degrees) * M_PI / 180.0)
#define to_degrees(radians) ((double)(radians) * 180.0 / M_PI)
    
void Camera::helpConstruct (
    const Point& location,
    const int image_height,
    const int image_width,
    const double horizontal_fov,
    const double focal_length,
    const double focal_angle,
    const Point& looking_at,
    const UnitVector<3>& up_direction
) {
    this->location = location;
    this->image_height = image_height;
    this->image_width = image_width;
    this->horizontal_fov = horizontal_fov;
    this->focal_length = focal_length;
    this->focal_radius = focal_length * tan(focal_angle / 2.0);
    this->view_direction = looking_at - this->location;
    this->up_direction = up_direction;
    this->view_horz = cross(up_direction, view_direction);
    this->view_vert = cross(view_direction, view_horz);
    this->view_width = 2.0 * this->focal_length * tan(to_radians(this->horizontal_fov) / 2);
    this->pixel_width = this->view_width / this->image_width;
}

Camera::Camera (
    const Point& location,
    const int image_height,
    const int image_width,
    const double horizontal_fov,
    const double vertical_fov,
    const double focal_length,
    const double focal_angle,
    const Point& looking_at,
    const UnitVector<3>& up_direction
) {
    helpConstruct (
        location,
        image_height,
        image_width,
        horizontal_fov,
        focal_length,
        focal_angle,
        looking_at,
        up_direction
    );
    this->view_height = 2.0 * this->focal_length * tan(to_radians(this->vertical_fov) / 2.0);
    this->pixel_height = this->view_height / this->image_height;
    this->vertical_fov = vertical_fov;
}

Camera::Camera (
    const Point& location,
    const int image_height,
    const int image_width,
    const double horizontal_fov,
    const double focal_length,
    const double focal_angle,
    const Point& looking_at,
    const UnitVector<3>& up_direction
) {
    helpConstruct(
        location,
        image_height,
        image_width,
        horizontal_fov,
        focal_length,
        focal_angle,
        looking_at,
        up_direction
    );
    this->view_height = this->view_width * image_height / image_width;
    this->pixel_height = this->view_height / this->image_height;
    this->vertical_fov = to_degrees(atan((this->view_height / 2.0) / this->focal_length) * 2.0);
}

Camera::Camera (
    const Point& location,
    const int image_height,
    const int image_width,
    const double horizontal_fov,
    const double focal_length,
    const double focal_angle,
    const Point& looking_at
) 
    : Camera (
        location,
        image_height,
        image_width,
        horizontal_fov,
        focal_length,
        focal_angle,
        looking_at,
        {{0.0, 1.0, 0.0}}
    )
{ }

Camera::Camera (
    const Point& location,
    const int image_height,
    const int image_width,
    const double horizontal_fov,
    const double focal_length,
    const Point& looking_at
)
    : Camera (
        location,
        image_height,
        image_width,
        horizontal_fov,
        focal_length,
        0,
        looking_at
    )
{ }

Camera::Camera (
    const Point& location,
    const int image_height,
    const int image_width,
    const double horizontal_fov,
    const Point& looking_at
)
    : Camera (
        location,
        image_height,
        image_width,
        horizontal_fov,
        length((Vector<3>)(looking_at - location)),
        looking_at
    )
{ }

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

Ray Camera::generate_ray (const int row, const int col) const {

    double x_position = col * pixel_width;
    double y_position = row * pixel_height;

    Vector<2> sample_offset = randomInUnitCircle();
    double sample_x_offset = sample_offset[0] * pixel_width;
    double sample_y_offset = sample_offset[1] * pixel_height;

    double global_x_offset = this->view_width / 2;
    double global_y_offset = this->view_height / 2;

    Vector<3> view_direction {
        this->view_horz * (x_position + sample_x_offset - global_x_offset) + \
        this->view_vert * (y_position + sample_y_offset - global_y_offset) + \
        this->view_direction * (this->focal_length)
    };

    Vector<2> focus_offset = this->focal_radius * randomInUnitCircle();
    Point location = this->location + (this->view_horz * focus_offset[0]) + (this->view_vert * focus_offset[1]);

    return {
        location,
        view_direction
    };
}

std::vector<Color> Camera::capture (const std::list<Intersectable*> scene, const int samples_per_pixel, const int steps_per_sample) const {

    std::cout << "Rendering image...\n";

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

    return SKYBLUE;
}
