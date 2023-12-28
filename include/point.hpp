#ifndef POINT_HPP
#define POINT_HPP

template <unsigned int height>
requires (0 < height)
class Vector;

using Point = Vector<3>;

#endif