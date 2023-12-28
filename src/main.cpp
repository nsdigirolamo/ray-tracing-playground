#include "color.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "image.hpp"

int main () {

    constexpr double width = 2.0;
    constexpr double height = 1.0;
    double window_distance = 1.0;

    constexpr int image_width = 1000;
    constexpr int image_height = image_width * (height / width);

    static Color pixels[image_height][image_width];

    Point camera_origin {{0, 0, 0}};

    Point sphere_location = {{0, 0, 2.0}};
    double radius = 0.5;
    Sphere sphere = {sphere_location, radius};

    double width_delta = width / image_width;
    double height_delta = height / image_height;

    for (int row = 0; row < image_height; row++) {
        for (int col = 0; col < image_width; col++) {

            Vector<3> direction {{
                col * width_delta - (width / 2),
                row * height_delta - (height / 2),
                window_distance
            }};

            Ray ray {camera_origin, direction};

            if (sphere.intersects(ray)) {
                pixels[row][col] = {{255, 0, 0}};
            } else {
                pixels[row][col] = {{0, 0,0 }};
            }
        }
    }

   generate_ppm(pixels, "sphere");
}