#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <fstream>
#include "color.hpp"

using namespace std;

template<size_t width, size_t height>
void generate_ppm (const array<array<Color, width>, height> pixels, const string file_name) {

    ofstream file(file_name + ".ppm");
    file << "P3\n" << width << " " << height << "\n" << "255\n";

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Color pixel = pixels[row][col];
            file << pixel[0] << " " << pixel[1] << " " << pixel[2] << "\n";
        }
    }
}

void generate_test ();

#endif