#include "primitives/color.hpp"

void writePixel (std::ofstream& file, Color pixel) {

    int r = pixel[0] * 255;
    int g = pixel[1] * 255;
    int b = pixel[2] * 255;

    file << r << " " << g << " " << b << "\n";
}

void writeImage (const std::string file_name, std::vector<Color>& pixels, int image_height, int image_width) {

    std::cout << "Printing image to file...\n";

    std::ofstream file(file_name + ".ppm");

    file << "P3\n\n" << image_width << " " << image_height << "\n" << "255\n";

    for (int row = image_height - 1; 0 <= row; --row) {
        for (int col = 0; col < image_width; ++col) {
            writePixel(file, pixels[(row * image_width) + col]);
        }
    }

    std::cout << "Done printing to file!\n";
}