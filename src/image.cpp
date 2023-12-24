#include <array>
#include "color.hpp"
#include "image.hpp"

void generate_test () {

    array<array<Color, 3>, 2> pixels = {{
        {{ {255, 0, 0}, {0, 255, 0}, {0, 0, 255} }},
        {{ {255, 255, 0}, {255, 255, 255}, {0, 0, 0} }}
    }};

    generate_ppm(pixels, "test");
}