#include "matrix.hpp"
#include "test/test_utils.hpp"

bool testMultBasic () {

    Matrix<3, 3> m1 { {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    } };

    double scalar = 2.0;

    Matrix<3, 3> m2 { {
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}
    } };

    Matrix<3, 3> m3 = m1 * 2.0;
    return printTest("testMultBasic", isApprox(m2, m3, EPSILON), m2);
}

bool testMultReverseBasic () {

    Matrix<3, 3> m1 { {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    } };

    double scalar = 2.0;

    Matrix<3, 3> m2 { {
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}
    } };

    Matrix<3, 3> m3 = 2.0 * m1;
    return printTest("testMultReverseBasic", isApprox(m2, m3, EPSILON), m2);
}

bool testDivBasic () {

    Matrix<3, 3> m1 { {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    } };

    double scalar = 2.0;

    Matrix<3, 3> m2 { {
        {0.5, 1.0, 1.5},
        {2.0, 2.5, 3.0},
        {3.5, 4.0, 4.5}
    } };

    Matrix<3, 3> m3 = m1 / 2.0;
    return printTest("testDivBasic", isApprox(m2, m3, EPSILON), m2);
}

bool testHadamard () {

    Matrix<3, 3> m1 { {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    } };

    Matrix<3, 3> m2 { {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    } };

    Matrix<3, 3> m3 { {
        {1.0, 4.0, 9.0},
        {16.0, 25.0, 36.0},
        {49.0, 64.0, 81.0}
    } };

    Matrix<3, 3> m4 = hadamard(m1, m2);

    return printTest("testHadamard", isApprox(m4, m3, EPSILON), m4);
}

void doMatrixMultTests () {

    testMultBasic();
    testMultReverseBasic();
    testDivBasic();
    testHadamard();

}