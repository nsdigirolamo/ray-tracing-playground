#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <iostream>

using namespace std;

template <unsigned int rows, unsigned int columns>
class Matrix {

    private:

        double values[rows][columns];

    public:

        Matrix () {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    values[r][c] = 0.0;
                }
            }
        }

        Matrix (double (&values)[rows][columns]) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    this->values[r][c] = values[r][c];
                }
            }
        }

        Matrix<rows, columns>& operator+= (const Matrix<rows, columns>& rhs) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    values[r][c] += rhs.values[r][c];
                }
            }
            return *this;
        }

        Matrix<rows, columns>& operator-= (const Matrix<rows, columns>& rhs) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    values[r][c] -= rhs.values[r][c];
                }
            }
            return *this;
        }

        Matrix<rows, columns>& operator*= (const double& rhs) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    values[r][c] *= rhs;
                }
            }
            return *this;
        }

        Matrix<rows, columns>& operator/= (const double& rhs) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    values[r][c] /= rhs;
                }
            }
            return *this;
        }

        const double& operator[] (unsigned int row, unsigned int column) const {
            assert((row < rows) && "Matrix row out of bounds!");
            assert((column < columns) && "Matrix column out of bounds!");
            return values[row][column];
        }
};

template <unsigned int rows, unsigned int columns>
Matrix<rows, columns> operator* (const Matrix<rows, columns>& lhs, const double& rhs) {
    Matrix<rows, columns> result = lhs;
    result *= rhs;
    return result;
}

template <unsigned int rows, unsigned int columns>
Matrix<rows, columns> operator* (const double& lhs, const Matrix<rows, columns>& rhs) {
    return rhs * lhs;
}

template <unsigned int rows, unsigned int columns>
Matrix<rows, columns> operator/ (const Matrix<rows, columns>& lhs, const double& rhs) {
    Matrix<rows, columns> result = lhs;
    result /= rhs;
    return result;
}

template <unsigned int rows, unsigned int columns>
bool operator== (const Matrix<rows, columns>& lhs, const Matrix<rows, columns>& rhs) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (lhs[r][c] != rhs[r][c]) {
                return false;
            }
        }
    }
    return true;
}

template <unsigned int rows, unsigned int columns>
bool operator!= (const Matrix<rows, columns>& lhs, const Matrix<rows, columns>& rhs) {
    return !(lhs == rhs);
}

template <unsigned int rows, unsigned int columns>
ostream& operator<< (ostream& output, const Matrix<rows, columns>& matrix) {
    for (unsigned int r = 0; r < rows; r++) {
        output << "[ ";
        for (unsigned int c = 0; c < columns; c++) {
            output << matrix[r, c] << " ";
        }
        output << "]\n";
    }
    return output;
}

#endif