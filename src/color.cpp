#include "primitives/color.hpp"

Color::Color () {
    *this = {0.0, 0.0, 0.0};
}

Color::Color (const double r, const double g, const double b) {
    *this = (Vector<3>){{r, g, b}};
}

Color::Color (const double (&values)[3]) {
    *this = (Vector<3>)(values);
}

Color::Color (const Matrix<3, 1>& matrix) {
    *this = (Vector<3>)(matrix);
}

Color::Color (const Vector<3>& vector) {
    for (int i = 0; i < 3; ++i) {
        this->values[i][0] = vector[i];
    }
}

Color::Color (const int rgb_hex_value) {

    assert(0x000000 <= rgb_hex_value && rgb_hex_value <= 0xFFFFFF);

    int val = rgb_hex_value;

    double b = val % 0x100;
    double g = (val >> 8) % 0x100;
    double r = (val >> 16);

    *this = {r / 256, g / 256, b / 256};
}

Color gamma_correct (const Color& color) {

    double gamma = 2.2;
    double exp = 1.0 / gamma;

    return {{
        std::pow(color[0], exp),
        std::pow(color[1], exp),
        std::pow(color[2], exp)
    }};
}

void writePixel (std::ofstream& file, const Color& pixel) {

    int r = pixel[0] * 255.0;
    int g = pixel[1] * 255.0;
    int b = pixel[2] * 255.0;

    file << r << " " << g << " " << b << "\n";
}

void writeImage (const std::string file_name, const std::vector<Color>& pixels, int image_height, int image_width) {

    std::cout << "Printing image to file...\n";

    std::ofstream file(file_name + ".ppm");

    file << "P3\n\n" << image_width << " " << image_height << "\n" << "255\n";

    for (int row = image_height - 1; 0 <= row; --row) {
        for (int col = 0; col < image_width; ++col) {
            writePixel(
                file,
                gamma_correct(pixels[(row * image_width) + col])
            );
        }
    }

    std::cout << "Done printing to file!\n";
}
