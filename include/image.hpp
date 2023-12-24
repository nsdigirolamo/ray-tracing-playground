#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include "color.hpp"

using namespace std;

void generate_ppm (Color** pixels, unsigned int width, unsigned int height, const string file_name);
void generate_test ();

#endif