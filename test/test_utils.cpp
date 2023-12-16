#include <cmath>

bool floatApprox (const double a, const double b, const double epsilon) {
    return fabs(a - b) < epsilon;
}