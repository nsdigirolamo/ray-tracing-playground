#include "vector.hpp"
#include <iostream>

using namespace std;

int main () {

    double my_vector[3] = { 3.1, 2.2, 1.3 };

    Vector<3> v1 {my_vector};

    cout << v1 << "\n";
}