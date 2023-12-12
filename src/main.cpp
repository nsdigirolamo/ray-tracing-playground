#include "matrix.hpp"
#include <iostream>

using namespace std;

int main () {

    double my_array[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    Matrix<3, 3> my_matrix {my_array};

    cout << my_matrix;
}