#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "matrix.hpp"

#define EPSILON 0.00001

template <unsigned int height, unsigned int width>
bool printTest(const char* test_name, bool is_success, Matrix<height, width> result) {
    if (is_success) {
        cout << test_name << " completed successfully.\n";
        return true;
    } else {
        cout << test_name << " failed with resulting matrix:\n" << result << "\n";
        return false;
    }
}

#endif
