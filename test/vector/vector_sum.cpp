#include "test/test_utils.hpp"
#include "vector.hpp"

bool testVectorSumBasic () {

    Vector<3> v1 { 1.0, 2.0, 3.0 };
    Vector<3> v2 { 1.0, 2.0, 3.0 };
    Vector<3> v3 { 2.0, 4.0, 6.0 };
    Vector<3> v4 = v1 + v2;

    return printTest("testVectorSumBasic", isApprox(v4, v3, EPSILON), v4);
}

bool testVectorDiffBasic () {

    Vector<3> v1 { 1.0, 2.0, 3.0 };
    Vector<3> v2 { 9.0, 8.0, 7.0 };
    Vector<3> v3 { -8.0, -6.0, -4.0};
    Vector<3> v4 = v1 - v2;

    return printTest("testVectorDiffBasic", isApprox(v4, v3, EPSILON), v4);
}

bool testVectorDiffReverse () {

    Vector<3> v1 { 1.0, 2.0, 3.0 };
    Vector<3> v2 { 9.0, 8.0, 7.0 };
    Vector<3> v3 { 8.0, 6.0, 4.0};
    Vector<3> v4 = v2 - v1;

    return printTest("testVectorDiffReverse", isApprox(v4, v3, EPSILON), v4);
}

bool testVectorFloatingPointSum () {

    Vector<3> v1 { 1.25, 2.50, 3.75 };
    Vector<3> v2 { 2.50, 3.75, 4.15 };
    Vector<3> v3 { 3.75, 6.25, 7.90 };
    Vector<3> v4 = v1 + v2;

    return printTest("testVectorFloatingPointSum", isApprox(v4, v3, EPSILON), v4);
}

void doVectorSumTests () {

    testVectorSumBasic();
    testVectorDiffBasic();
    testVectorDiffReverse();
    testVectorFloatingPointSum();

}