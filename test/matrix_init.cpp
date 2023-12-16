#include "matrix.hpp"
#include "test/test_utils.hpp"

bool basicInit () {

    Matrix<3, 3> matrix;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            bool is_approx = floatApprox(matrix[r, c], 0.0, EPSILON);
            if (!is_approx) return printTest("basicInit", false, matrix);
        }
    }

    return printTest("basicInit", true, matrix);
}

void doMatrixInitTests () {

    basicInit();

}