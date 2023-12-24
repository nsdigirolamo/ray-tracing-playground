#include <array>
#include <fstream>
#include <iostream>
#include "color.hpp"

using namespace std;

template<size_t width, size_t height>
void generate_ppm (const array<array<Color, width>, height> pixels, const string file_name) {

    ofstream out(file_name + ".ppm");
    out << "P3\n" << width << " " << height << "\n" << "255\n";

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Color pixel = pixels[row][col];
            out << pixel[0] << " " << pixel[1] << " " << pixel[2] << "\n";
        }
    }
}

void generate_test () {

    array<array<Color, 3>, 2> pixels = {{
        {{ {255, 0, 0}, {0, 255, 0}, {0, 0, 255} }},
        {{ {255, 255, 0}, {255, 255, 255}, {0, 0, 0} }}
    }};

    generate_ppm(pixels, "test");
}