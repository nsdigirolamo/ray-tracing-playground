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

    this->focal_distance = focal_length;
    this->focal_radius = focal_length * tan(to_radians(focal_angle) / 2.0);

    this->view_direction = looking_at - this->location;
    this->up_direction = up_direction;
    this->view_horizontal = cross(view_direction, up_direction);
    this->view_vertical = cross(view_horizontal, view_direction);

    this->view_width = 2.0 * this->focal_distance * tan(to_radians(this->horizontal_fov) / 2.0);
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
    this->view_height = 2.0 * this->focal_distance * tan(to_radians(this->vertical_fov) / 2.0);
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
    this->vertical_fov = to_degrees(atan((this->view_height / 2.0) / this->focal_distance) * 2.0);
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

double Camera::getFocalDistance () const {
    return this->focal_distance;
}

double Camera::getFocalRadius () const {
    return this->focal_radius;
}

double Camera::getPixelHeight () const {
    return this->pixel_height;
}

double Camera::getPixelWidth () const {
    return this->pixel_width;
}

UnitVector<3> Camera::getUpDirection () const {
    return this->up_direction;
}

UnitVector<3> Camera::getViewDirection () const {
    return this->view_direction;
}

UnitVector<3> Camera::getViewVertical () const {
    return this->view_vertical;
}

UnitVector<3> Camera::getViewHorizontal () const {
    return this->view_horizontal;
}

Point Camera::generateRayOrigin () const {
    Vector<2> offset = randomInUnitCircle();
    return this->location +
        (offset[0] * this->focal_radius * this->view_horizontal) +
        (offset[1] * this->focal_radius * this->view_vertical);
}

Point Camera::calculatePixelLocation (const int row, const int col, const bool is_anti_aliased) const {

    double x = col * this->pixel_width - 0.5 * this->pixel_width - 0.5 * this->view_width;
    double y = row * this->pixel_height - 0.5 * this->pixel_height - 0.5 * this->view_height;

    if (is_anti_aliased) {
        Vector<2> random_offset = randomInUnitCircle();
        x += random_offset[0] * this->pixel_width;
        y += random_offset[1] * this->pixel_height;
    }

    return
        this->view_horizontal * x +
        this->view_vertical * y +
        this->view_direction * this->focal_distance;
}

std::vector<Color> Camera::capture (const std::list<Intersectable*> scene, const int samples_per_pixel, const int steps_per_sample) const {

    std::cout << "Rendering image...\n";

    std::vector<Color> pixels (this->image_width * this->image_height);

    for (int row = this->image_height - 1; 0 <= row; --row) {
        for (int col = 0; col < this->image_width; ++col) {

            Color color = {{0, 0, 0}};

            for (int sample = 0; sample < samples_per_pixel; ++sample) {

                Point origin = this->generateRayOrigin();
                UnitVector<3> direction = this->calculatePixelLocation(row, col) - origin;

                Ray ray { origin, direction };
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

        bool hit_is_closest =
            hit.has_value() &&
            closest.has_value() &&
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

        --steps;

        if (0 < steps) {
            Color traced_color = trace(material.scatter(hit), intersectables, steps);
            return hadamard(material_color, traced_color);
        }

        return material_color;
    }

    return SKYBLUE;
}
