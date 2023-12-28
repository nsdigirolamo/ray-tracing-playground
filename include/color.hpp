#ifndef COLOR_HPP
#define COLOR_HPP

template <unsigned int height>
requires (0 < height)
class Vector;

using Color = Vector<3>;

#endif