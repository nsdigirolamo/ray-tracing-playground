#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"

template <unsigned int height>
requires (0 < height)
class Vector: public Matrix<height, 1> {

    public:

    double& operator[] (const unsigned int row) {
        assert(row < height);
        return this->values[row][0];
    }

    const double& operator[] (const unsigned int row) const {
        assert(row < height);
        return this->values[row][0];
    }
};

#endif