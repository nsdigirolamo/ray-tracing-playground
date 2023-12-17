#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

template <unsigned int height, unsigned int width>
requires (0 < height && 0 < width)
class Matrix {

    protected:

    double values[height][width];

    public:

    Matrix () {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                values[row][col] = 0.0;
            }
        }
    }

    Matrix (const double (&values)[height][width]) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                this->values[row][col] = values[row][col];
            }
        }
    }

    Matrix<height, width>& operator+= (const Matrix<height, width>& rhs) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                values[row][col] += rhs[row, col];
            }
        }
        return *this;
    }

    Matrix<height, width>& operator-= (const Matrix<height, width>& rhs) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                values[row][col] -= rhs[row, col];
            }
        }
        return *this;
    }

    Matrix<height, width>& operator*= (const double rhs) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                values[row][col] *= rhs;
            }
        }
        return *this;
    }

    Matrix<height, width>& operator/= (const double rhs) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                values[row][col] /= rhs;
            }
        }
        return *this;
    }

    double& operator[] (const unsigned int row, const unsigned int col) {
        assert(row < height);
        assert(col < width);
        return values[row][col];
    }

    const double& operator[] (const unsigned int row, const unsigned int col) const {
        assert(row < height);
        assert(col < width);
        return values[row][col];
    }
};

template <unsigned int height, unsigned int width>
Matrix<height, width> operator+ (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs) {
    Matrix<height, width> result = lhs;
    result += rhs;
    return result;
}

template <unsigned int height, unsigned int width>
Matrix<height, width> operator- (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs) {
    Matrix<height, width> result = lhs;
    result -= rhs;
    return result;
}

template <unsigned int height, unsigned int width>
Matrix<height, width> operator* (const Matrix<height, width>& lhs, const double& rhs) {
    Matrix<height, width> result = lhs;
    result *= rhs;
    return result;
}

template <unsigned int height, unsigned int width>
Matrix<height, width> operator* (const double& lhs, const Matrix<height, width>& rhs) {
    Matrix<height, width> result = rhs;
    result *= lhs;
    return result;
}

template <unsigned int height, unsigned int width>
Matrix<height, width> operator/ (const Matrix<height, width>& lhs, const double& rhs) {
    Matrix<height, width> result = lhs;
    result /= rhs;
    return result;
}

template <unsigned int height, unsigned int width>
bool operator== (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (lhs[row, col] == rhs[row, col]) return false;
        }
    }
    return true;
}

template <unsigned int height, unsigned int width>
bool isApprox (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs, const double epsilon) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (epsilon < fabs(lhs[row, col] - rhs[row, col])) return false;
        }
    }
    return true;
}

template <unsigned int height, unsigned int width>
bool operator!= (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs) {
    return !(lhs == rhs);
}

template <unsigned int height, unsigned int width>
ostream& operator<< (ostream& output, const Matrix<height, width>& m) {

    output << "[ ";
    for (int col = 0; col < width; col++) {
        output << m[0, col] << " ";
    }
    output << "]\n";

    for (int row = 1; row < height; row++) {
        output << "[ ";
        for (int col = 0; col < width; col++) {
            output << m[row, col] << " ";
        }
        output << "]\n";
    }
    return output;
}

#endif
