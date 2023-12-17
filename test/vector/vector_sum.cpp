#include "test/test_utils.hpp"
#include "vector.hpp"

bool testVectorSumBasic () {

    Vector<3> v1 { 1.0, 2.0, 3.0 };
    Vector<3> v2 { 1.0, 2.0, 3.0 };
    Vector<3> v3 { 2.0, 4.0, 6.0 };
    Vector<3> v4 = v1 + v2;

    return printTest("testVectorSumBasic", isApprox(v4, v3, EPSILON), v4);
}

void doVectorSumTests () {

    testVectorSumBasic();

}