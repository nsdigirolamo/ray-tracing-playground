#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"

using namespace std;

template <unsigned int height>
requires (0 < height)
class Vector: public Matrix<height, 1> {

    public:

    Vector () {
        for (int row = 0; row < height; row++) {
            this->values[row][0] = 0.0;
        }
    }

    Vector (const double (&values)[height]) {
        for (int row = 0; row < height; row++) {
            this->values[row][0] = values[row];
        }
    }

    Vector (const Matrix<height, 1>& m) {
        for (int row = 0; row < height; row++) {
            this->values[row][0] = m[row, 0];
        }
    }

    double length () {
        return sqrtf(dot(*this, *this));
    }

    Vector<height> direction () {
        return *this / this->length();
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

template <unsigned int height>
double dot (const Vector<height>& lhs, const Vector<height>& rhs) {
    double dot_product = 0.0;
    for (int row = 0; row < height; row++) {
        dot_product += lhs[row] * rhs[row];
    }
    return dot_product;
}

#endif