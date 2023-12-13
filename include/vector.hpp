#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <iostream>

using namespace std;

template <unsigned int length>
concept Nonzero = 0 < length;

template <unsigned int length>
requires Nonzero<length>
class Vector {

    private:

    double vector[length];

    public:

    Vector () {
        for (int i = 0; i < length; i++) {
            vector[i] = 0.0;
        }
    }

    Vector (const double (&vector)[length]) {
        for (int i = 0; i < length; i++) {
            this->vector[i] = vector[i];
        }
    }

    Vector<length>& operator+= (const Vector<length>& rhs) {
        for (int i = 0; i < length; i++) {
            this->vector[i] += rhs[i];
        }
        return *this;
    }

    Vector<length>& operator-= (const Vector<length>& rhs) {
        for (int i = 0; i < length; i++) {
            this->vector[i] -= rhs[i];
        }
        return *this;
    }

    Vector<length>& operator*= (const double& rhs) {
        for (int i = 0; i < length; i++) {
            this->vector[i] *= rhs;
        }
        return *this;
    }

    Vector<length>& operator/= (const double& rhs) {
        for (int i = 0; i < length; i++) {
            this->vector[i] /= rhs;
        }
        return *this;
    }

    double operator[] (const unsigned int index) const {
        assert(index < length);
        return vector[index];
    }
};

template <unsigned int length>
Vector<length> operator+ (const Vector<length>& lhs, const Vector<length>& rhs) {
    Vector<length> result = lhs;
    result += rhs;
    return result;
}

template <unsigned int length>
Vector<length> operator- (const Vector<length>& lhs, const Vector<length>& rhs) {
    Vector<length> result = lhs;
    result -= rhs;
    return result;
}

template <unsigned int length>
Vector<length> operator* (const Vector<length>& lhs, const double& rhs) {
    Vector<length> result = lhs;
    result *= rhs;
    return result;
}

template <unsigned int length>
Vector<length> operator* (const double& lhs, const Vector<length>& rhs) {
    return rhs * lhs;
}

template <unsigned int length>
Vector<length> operator/ (const Vector<length>& lhs, const double& rhs) {
    Vector<length> result = lhs;
    result /= rhs;
    return result;
}

template <unsigned int length>
bool operator== (const Vector<length>& lhs, const Vector<length>& rhs) {
    for (int i = 0; i < length; i++) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

template <unsigned int length>
bool operator!= (const Vector<length>& lhs, const Vector<length>& rhs) {
    return !(lhs == rhs);
}

template <unsigned int length>
ostream& operator<< (ostream& output, const Vector<length>& v) {
    output << "[ " << v[0] << " ]";
    for (int i = 1; i < length; i++) {
        output << "\n[ " << v[i] << " ]";
    }
    return output;
}

#endif
