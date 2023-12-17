#include <iostream>

#include "test/matrix_init.hpp"
#include "test/matrix_mult.hpp"
#include "test/matrix_sum.hpp"

using namespace std;

int main () {

    cout << "--------------------\nMatrix Sum Tests:\n--------------------\n";
    doMatrixSumTests();
    cout << "--------------------\nMatrix Init Tests:\n--------------------\n";
    doMatrixInitTests();
    cout << "--------------------\nMatrix Mult Tests:\n--------------------\n";
    doMatrixMultTests();

}