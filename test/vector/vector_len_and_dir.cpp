#include "test/test_utils.hpp"
#include "vector.hpp"

bool testDot () {

    Vector<2> v1 { 2.0, 1.0 };
    Vector<2> v2 { 1.0, 6.0 };

    return printTest("testDot", floatApprox(dot(v1, v2), 8.0, EPSILON), v1);
}

bool testLength () {

    Vector<3> vector { 1.0, 2.0, 3.0 };

    return printTest("testLength", floatApprox(vector.length(), 3.74165, EPSILON), vector);
}

bool testDirection () {

    Vector<3> vector { 2.34, 3.5, 6.7 };
    Vector<3> direction { 0.29571, 0.44231, 0.84670 };

    return printTest("testDirection", isApprox(vector.direction(), direction, EPSILON), vector);
}

void doVectorLenAndDirTests () {

    testDot();
    testLength();
    testDirection();

}