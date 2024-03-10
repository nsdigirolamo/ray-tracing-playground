#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <cmath>
#include <iostream>
#include <cuda.h>
#include <cuda_runtime.h>

template <unsigned int row_count>
class Vector;

template <unsigned int column_count>
class MatrixRow {

    private:

    double columns[column_count];

    public:

    __host__ __device__ double& operator[] (const unsigned int col) {
        assert(col < column_count);
        return this->columns[col];
    }

    __host__ __device__ const double& operator[] (const unsigned int col) const {
        assert(col < column_count);
        return this->columns[col];
    }
};

template <unsigned int row_count, unsigned int column_count>
class Matrix {

    protected:

    MatrixRow<column_count> values[row_count];

    public:

    __host__ __device__ Matrix () {
        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < column_count; ++col) {
                this->values[row][col] = 0;
            }
        }
    }

    Matrix (const double (&values)[row_count][column_count]) {
        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < column_count; ++col) {
                this->values[row][col] = values[row][col];
            }
        }
    }

    Matrix<row_count, column_count>& operator+= (const Matrix<row_count, column_count>& rhs) {
        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < column_count; ++col) {
                this->values[row][col] += rhs[row][col];
            }
        }
        return *this;
    }

    Matrix<row_count, column_count>& operator-= (const Matrix<row_count, column_count>& rhs) {
        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < column_count; ++col) {
                this->values[row][col] -= rhs[row][col];
            }
        }
        return *this;
    }

    __host__ __device__ Matrix<row_count, column_count>& operator*= (const double rhs) {
        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < column_count; ++col) {
                this->values[row][col] *= rhs;
            }
        }
        return *this;
    }

    Matrix<row_count, column_count>& operator/= (const double rhs) {
        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < column_count; ++col) {
                this->values[row][col] /= rhs;
            }
        }
        return *this;
    }

    __host__ __device__ MatrixRow<column_count>& operator[] (const unsigned int row) {
        assert(row < row_count);
        return this->values[row];
    }

    __host__ __device__ const MatrixRow<column_count>& operator[] (const unsigned int row) const {
        assert(row < row_count);
        return this->values[row];
    }

    Vector<row_count> transform (const Vector<row_count>& vector) const {

        Vector<row_count> result;

        for (int col = 0; col < column_count; ++col) {
            Vector<row_count> temp;
            for (int row = 0; row < row_count; ++row) {
                temp[row] = this->values[row][col];
            }
            result += vector[col] * temp;
        }

        return result;
    }

    unsigned int height () const {
        return row_count;
    }

    unsigned int width () const {
        return column_count;
    }
};

template <unsigned int row_count, unsigned int column_count>
Matrix<row_count, column_count> operator+ (const Matrix<row_count, column_count>& lhs, const Matrix<row_count, column_count>& rhs) {
    Matrix<row_count, column_count> result = lhs;
    result += rhs;
    return result;
}

template <unsigned int row_count, unsigned int column_count>
Matrix<row_count, column_count> operator- (const Matrix<row_count, column_count>& lhs, const Matrix<row_count, column_count>& rhs) {
    Matrix<row_count, column_count> result = lhs;
    result -= rhs;
    return result;
}

template <unsigned int row_count, unsigned int column_count>
Matrix<row_count, column_count> operator* (const Matrix<row_count, column_count>& lhs, const double& rhs) {
    Matrix<row_count, column_count> result = lhs;
    result *= rhs;
    return result;
}

template <unsigned int row_count, unsigned int column_count>
Matrix<row_count, column_count> operator* (const double& lhs, const Matrix<row_count, column_count>& rhs) {
    Matrix<row_count, column_count> result = rhs;
    result *= lhs;
    return result;
}

template<unsigned int row_count, unsigned int column_count>
Matrix<row_count, column_count> hadamard (const Matrix<row_count, column_count>& lhs, const Matrix<row_count, column_count>& rhs) {
    Matrix<row_count, column_count> result;
    for (int row = 0; row < row_count; row++) {
        for (int col = 0; col < column_count; col++) {
            result[row][col] = lhs[row][col] * rhs[row][col];
        }
    }
    return result;
}

template <unsigned int row_count, unsigned int column_count>
Matrix<row_count, column_count> operator/ (const Matrix<row_count, column_count>& lhs, const double& rhs) {
    Matrix<row_count, column_count> result = lhs;
    result /= rhs;
    return result;
}

template <unsigned int row_count, unsigned int column_count>
bool operator== (const Matrix<row_count, column_count>& lhs, const Matrix<row_count, column_count>& rhs) {
    for (int row = 0; row < row_count; row++) {
        for (int col = 0; col < column_count; col++) {
            if (lhs[row][col] != rhs[row][col]) return false;
        }
    }
    return true;
}

template <unsigned int row_count, unsigned int column_count>
bool isApprox (const Matrix<row_count, column_count>& lhs, const Matrix<row_count, column_count>& rhs, const double epsilon = 0.001) {
    for (int row = 0; row < row_count; row++) {
        for (int col = 0; col < column_count; col++) {
            if (epsilon < fabs(lhs[row][col] - rhs[row][col])) return false;
        }
    }
    return true;
}

template <unsigned int row_count, unsigned int column_count>
bool operator!= (const Matrix<row_count, column_count>& lhs, const Matrix<row_count, column_count>& rhs) {
    return !(lhs == rhs);
}

template <unsigned int row_count, unsigned int column_count>
std::ostream& operator<< (std::ostream& output, const Matrix<row_count, column_count>& matrix) {

    output << "[ ";
    for (int col = 0; col < column_count; col++) {
        output << matrix[0][col] << " ";
    }
    output << "]";

    for (int row = 1; row < row_count; row++) {
        output << "\n[ ";
        for (int col = 0; col < column_count; col++) {
            output << matrix[row][col] << " ";
        }
        output << "]";
    }
    return output;
}

template <unsigned int row_count>
Matrix<row_count, row_count> identity (const Matrix<row_count, row_count>& matrix) {
    Matrix<row_count, row_count> identity_matrix;
    for (int i = 0; i < row_count; i++) {
        identity_matrix[i][i] = 1.0;
    }
    return identity_matrix;
}

#endif
