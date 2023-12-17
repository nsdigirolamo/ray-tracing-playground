#include "test/test_utils.hpp"
#include "vector.hpp"

bool testDefaultVectorInit () {

    Vector<3> vector;

    for (int r = 0; r < 3; r++) {
        bool is_approx = floatApprox(vector[r], 0.0, EPSILON);
        if (!is_approx) return printTest("testDefaultVectorInit", false, vector);
    }

    return printTest("testDefaultVectorInit", true, vector);
}

bool testListVectorInit () {

    double my_array[3][1] { {1.0}, {2.0}, {3.0} };
    Vector<3> vector { 1.0, 2.0, 3.0 };

    for (int r = 0; r < 3; r++) {
        bool is_approx = floatApprox(vector[r], my_array[r][0], EPSILON);
        if (!is_approx) return printTest("testListVectorInit", false, vector);
    }

    return printTest("testListVectorInit", true, vector);
}

bool testArrayVectorInit () {

    double my_array[3][1] { {1.0}, {2.0}, {3.0} };
    Vector<3> vector { my_array };

    for (int r = 0; r < 3; r++) {
        bool is_approx = floatApprox(vector[r], my_array[r][0], EPSILON);
        if (!is_approx) return printTest("testArrayVectorInit", false, vector);
    }

    return printTest("testArrayVectorInit", true, vector);
}

bool testArrayVectorInitDeepCopy () {

    double my_array[3][1] { {1.0}, {2.0}, {3.0} };
    Vector<3> vector { my_array };

    my_array[0][0] = 0.0;

    return printTest(
        "testArrayVectorInitDeepCopy",
        !floatApprox(vector[0], my_array[0][0], EPSILON),
        vector
    );
}

bool testMatrixVectorInit () {

    Matrix<3, 1> matrix { { 
        { 1.0 }, 
        { 2.0 }, 
        { 3.0 } 
    } };
    Vector<3> vector { matrix };

    return printTest(
        "testMatrixVectorInit",
        isApprox(vector, matrix, EPSILON),
        vector
    );
}

bool testMatrixVectorInitDeepCopy () {

    Matrix<3, 1> matrix { { 
        { 1.0 }, 
        { 2.0 }, 
        { 3.0 } 
    } };
    Vector<3> vector { matrix };

    matrix[2, 0] = 0.0;

    return printTest(
        "testMatrixVectorInitDeepCopy",
        !isApprox(vector, matrix, EPSILON),
        vector
    );
}

bool testVectorIsEditable () {

    Vector<3> v1 { 1.0, 2.0, 3.0 };
    Vector<3> v2 { v1 };

    if (!isApprox(v1, v2, EPSILON)) {
        return printTest(
            "testVectorIsEditable",
            false,
            v1
        );
    }

    v1[0] = 0.0;

    return printTest(
        "testVectorIsEditable",
        !isApprox(v1, v2, EPSILON),
        v1
    );
}

void doVectorInitTests () {
    
    testDefaultVectorInit();
    testListVectorInit();
    testArrayVectorInit();
    testArrayVectorInitDeepCopy();
    testMatrixVectorInit();
    testMatrixVectorInitDeepCopy();
    testVectorIsEditable();

}