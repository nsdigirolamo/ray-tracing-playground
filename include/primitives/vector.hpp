#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

#include "primitives/matrix.hpp"

template <unsigned int row_count>
class Vector : public Matrix<row_count, 1> {

    public:

    Vector () {
        for (int row = 0; row < row_count; ++row) {
            this->values[row][0] = 0;
        }
    }

    Vector (const double (&values)[row_count]) {
        for (int row = 0; row < row_count; ++row) {
            this->values[row][0] = values[row];
        }
    }

    Vector (const Matrix<row_count, 1>& matrix) {
        for (int row = 0; row < row_count; ++row) {
            this->values[row][0] = matrix[row][0];
        }
    }

    double& operator[] (const unsigned int row) {
        assert(row < row_count);
        return this->values[row][0];
    }

    const double& operator[] (const unsigned int row) const {
        assert(row < row_count);
        return this->values[row][0];
    }

    double length_squared () const {
        return dot(*this, *this);
    }

    double length () const {
        return sqrtf(this->length_squared());
    }

    Vector<row_count> direction () const {
        return *this / this->length();
    }
};

template <unsigned int row_count>
class UnitVector: public Vector<row_count> {

    public:

    UnitVector () {
        for (int row = 0; row < row_count; ++row) {
            this->values[row][0] = 0;
        }
        this->values[0][0] = 1;
    }

    UnitVector (const Vector<row_count>& vector) {
        Vector<row_count> unit_vector = vector / vector.length();
        for (int row = 0; row < row_count; ++row) {
            this->values[row][0] = unit_vector[row];
        }
    }

    UnitVector (const double (&values)[row_count])
        : UnitVector((Vector<row_count>)(values))
    { }

    UnitVector (const Matrix<row_count, 1>& matrix)
        : UnitVector((Vector<row_count>)(matrix))
    { }
};

template <unsigned int row_count>
UnitVector<row_count> normalize (Vector<row_count> vector) {
    return (UnitVector<row_count>)(vector);
}

template <unsigned int row_count>
double dot (const Vector<row_count>& lhs, const Vector<row_count>& rhs) {
    double dot_product = 0.0;
    for (int row = 0; row < row_count; ++row) {
        dot_product += lhs[row] * rhs[row];
    }
    return dot_product;
}

#define cross(lhs, rhs) \
    (Vector<3>){{ \
        lhs[1] * rhs[2] - lhs[2] * rhs[1], \
        lhs[2] * rhs[0] - lhs[0] * rhs[2], \
        lhs[0] * rhs[1] - lhs[1] * rhs[0], \
    }}

template <unsigned int row_count>
Vector<row_count> reflect (const Vector<row_count>& vector, const Vector<row_count>& surface_normal) {
    Vector<row_count> normal = normalize(surface_normal);
    return vector - 2 * dot(vector, normal) * normal;
}

template <unsigned int row_count>
Vector<row_count> refract (const Vector<row_count>& vector, const Vector<row_count>& surface_normal, const double refractive_index) {

    Vector<row_count> v = normalize(vector);
    Vector<row_count> n = normalize(surface_normal);

    double cos_theta = dot((Vector<3>)(-1.0 * v), n);
    Vector<3> normal_orthogonal = refractive_index * (v + cos_theta * n);
    Vector<3> normal_parallel = -1.0 * sqrt(fabs(1.0 - normal_orthogonal.length_squared())) * n;

    return normal_orthogonal + normal_parallel;
}

typedef Vector<3> Point;

#endif