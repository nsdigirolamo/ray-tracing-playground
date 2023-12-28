#include <vector>
#include "color.hpp"
#include "image.hpp"

void generate_test () {

    Color pixels[2][3] = {
        { {{255, 0, 0}}, {{0, 255, 0}}, {{0, 0, 255}} },
        { {{255, 255, 0}}, {{255, 255, 255}}, {{0, 0, 0}} }
    };

    generate_ppm(pixels, "test");
}