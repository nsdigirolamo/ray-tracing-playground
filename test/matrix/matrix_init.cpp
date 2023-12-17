#include "matrix.hpp"
#include "test/test_utils.hpp"

bool defaultInit () {

    Matrix<3, 3> matrix;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            bool is_approx = floatApprox(matrix[r, c], 0.0, EPSILON);
            if (!is_approx) return printTest("defaultInit", false, matrix);
        }
    }

    return printTest("defaultInit", true, matrix);
}

bool arrayInit () {

    double my_array[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    Matrix<3, 3> matrix { my_array };

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            bool is_approx = floatApprox(matrix[r, c], my_array[r][c], EPSILON);
            if (!is_approx) return printTest("arrayInit", false, matrix);
        }
    }

    return printTest("arrayInit", true, matrix);
}

bool arrayInitIsDeep () {

    double my_array[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    Matrix<3, 3> matrix { my_array };

    my_array[0][0] = 100.0;

    return printTest(
        "arrayInitIsDeep",
        !floatApprox(matrix[0, 0], my_array[0][0], EPSILON),
        matrix
    );
}

bool setMatrixValue () {

    double my_array[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    Matrix<3, 3> matrix { my_array };

    matrix[0, 0] = 100.0;

    return printTest(
        "setMatrixValue",
        !floatApprox(matrix[0, 0], my_array[0][0], EPSILON),
        matrix
    );
}

void doMatrixInitTests () {

    defaultInit();
    arrayInit();
    arrayInitIsDeep();
    setMatrixValue();

}