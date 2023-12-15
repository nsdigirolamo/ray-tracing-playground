#include "matrix.hpp"
#include "test/test_utils.hpp"

bool testSumBasic () {

    Matrix<3, 3> m1 { {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    } };

    Matrix<3,3> m2 { {
        {9.0, 8.0, 7.0},
        {6.0, 5.0, 4.0},
        {3.0, 2.0, 1.0}
    } };

    Matrix<3, 3> m3 { {
        {10, 10, 10},
        {10, 10, 10},
        {10, 10, 10}
    } };

    Matrix<3, 3> m4 = m1 + m2;
    return printTest("testSumBasic", isApprox(m4, m3, EPSILON), m4);
}

bool testSumSingleFloatingPoints () {

    Matrix<1, 1> m1 { {
        {1}
    } };

    Matrix<1,1> m2 { {
        {100.123456789}
    } };

    Matrix<1, 1> m3 { {
        {101.123456789}
    } };

    Matrix<1, 1> m4 = m1 + m2;
    return printTest("testSumSingleFloatingPoints", isApprox(m4, m3, EPSILON), m4);
}

bool testSumManyFloatingPoints () {

    Matrix<4, 4> m1 { {
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}
    } };

    Matrix<4, 4> m2 { {
        {1.11, 2.22, 3.33, 4.44},
        {5.55, 6.66, 7.77, 8.88},
        {9.99, 10.1010, 11.1111, 12.1212},
        {13.1313, 14.1414, 15.1515, 16.1616}
    } };

    Matrix<4, 4> m3 { {
        {2.11, 4.22, 6.33, 8.44},
        {10.55, 12.66, 14.77, 16.88},
        {18.99, 20.1010, 22.1111, 24.1212},
        {26.1313, 28.1414, 30.1515, 32.1616}
    } };

    Matrix<4, 4> m4 = m1 + m2;
    return printTest("testSumManyFloatingPoints", isApprox(m4, m3, EPSILON), m4);
}

void doSumTests () {

    testSumBasic();
    testSumSingleFloatingPoints();
    testSumManyFloatingPoints();
}
