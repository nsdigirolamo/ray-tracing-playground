#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "matrix.hpp"

#define EPSILON 0.00001

template <unsigned int height, unsigned int width>
bool printTest(const char* test_name, bool is_success, Matrix<height, width> result) {
    if (is_success) {
        cout << "COMPLETED: " << test_name << "\n";
        return true;
    } else {
        cout << "FAILED: " << test_name << "\n" << result << "\n";
        return false;
    }
}

bool floatApprox (const double a, const double b, const double epsilon);

#endif
