#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <cmath>
#include <iostream>

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

    Matrix<height, 1> transform (const Matrix<width, 1>& vector) const {

        Matrix<height, 1> result;

        for (int col = 0; col < width; col++) {
            Matrix<height, 1> column;
            for (int row = 0; row < height; row++) {
                column[row, 0] = this->values[row][col];
            }
            result += vector[col, 0] * column;
        }

        return result;
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

template<unsigned int height, unsigned int width>
Matrix<height, width> hadamard (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs) {
    Matrix<height, width> result;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            result[row, col] = lhs[row, col] * rhs[row, col];
        }
    }
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
            if (lhs[row, col] != rhs[row, col]) return false;
        }
    }
    return true;
}

template <unsigned int height, unsigned int width>
bool isApprox (const Matrix<height, width>& lhs, const Matrix<height, width>& rhs, const double epsilon = 0.001) {
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
std::ostream& operator<< (std::ostream& output, const Matrix<height, width>& m) {

    output << "[ ";
    for (int col = 0; col < width; col++) {
        output << m[0, col] << " ";
    }
    output << "]";

    for (int row = 1; row < height; row++) {
        output << "\n[ ";
        for (int col = 0; col < width; col++) {
            output << m[row, col] << " ";
        }
        output << "]";
    }
    return output;
}

template <unsigned int height>
Matrix<height, height> identity (Matrix<height, height>& matrix) {
    Matrix<height, height> identity_matrix;
    for (int i = 0; i < height; i++) {
        identity_matrix[i, i] = 1.0;
    }
    return identity_matrix;
}

#endif
