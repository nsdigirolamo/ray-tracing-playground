#include <iostream>

#include "test/matrix/matrix_init.hpp"
#include "test/matrix/matrix_mult.hpp"
#include "test/matrix/matrix_sum.hpp"
#include "test/vector/vector_init.hpp"
#include "test/vector/vector_sum.hpp"

using namespace std;

int main () {

    cout << "--------------------\nMatrix Sum Tests:\n--------------------\n";
    doMatrixSumTests();
    cout << "--------------------\nMatrix Init Tests:\n--------------------\n";
    doMatrixInitTests();
    cout << "--------------------\nMatrix Mult Tests:\n--------------------\n";
    doMatrixMultTests();
    cout << "--------------------\nVector Sum Tests:\n--------------------\n";
    doVectorSumTests();
    cout << "--------------------\nVector Init Tests:\n--------------------\n";
    doVectorInitTests();

}