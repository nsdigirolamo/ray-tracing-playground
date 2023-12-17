#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"

using namespace std;

template <unsigned int height>
requires (0 < height)
class Vector: public Matrix<height, 1> {

    public:

    Vector (initializer_list<double> list) {
        initializer_list<double>::iterator it = list.begin();
        for (int row = 0; row < height; row++) {
            this->values[row][0] = *it;
            it++;
        }
    }

    Vector (const Matrix<height, 1> &m) {
        for (int row = 0; row < height; row++) {
            this->values[row][0] = m[row, 0];
        }
    }

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