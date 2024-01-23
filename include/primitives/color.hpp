#ifndef COLOR_HPP
#define COLOR_HPP

#include <fstream>
#include <ostream>
#include <vector>

#include "primitives/vector.hpp"

using Color = Vector<3>;

void writePixel (std::ofstream& file, Color pixel);
void writeImage (const std::string file_name, std::vector<Color>& pixels, int image_height, int image_width);

#endif