#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

#include "primitives/matrix.hpp"

template <unsigned int height>
requires (0 < height)
class Vector: public Matrix<height, 1> {

    public:

    /**
     * @brief Constructs a new Vector with 0 for all values.
     */
    Vector () {
        for (int row = 0; row < height; row++) {
            this->values[row][0] = 0.0;
        }
    }

    /**
     * @brief Constructs a new Vector where the elements of the Vector are the
     * same as the given array.
     *
     * @param values
     */
    Vector (const double (&values)[height]) {
        for (int row = 0; row < height; row++) {
            this->values[row][0] = values[row];
        }
    }

    /**
     * @brief Constructs a new Vector object where the elements of the Vector
     * are the same as the given Matrix.
     *
     * @param m
     */
    Vector (const Matrix<height, 1>& m) {
        for (int row = 0; row < height; row++) {
            this->values[row][0] = m[row, 0];
        }
    }

    /**
     * @brief Gets the value of the vector at the specified row.
     *
     * @param row
     * @return double&
     */
    double& operator[] (const unsigned int row) {
        assert(row < height);
        return this->values[row][0];
    }

    /**
     * @brief Gets the value of the vector at the specified row.
     *
     * @param row
     * @return const double&
     */
    const double& operator[] (const unsigned int row) const {
        assert(row < height);
        return this->values[row][0];
    }
};

/**
 * @brief Calculates the dot product between two given vectors.
 *
 * @tparam height The size of the given vectors.
 * @param lhs The vector on the left hand side of the equation.
 * @param rhs The vector on the right hand side of the equation.
 * @return double The dot product.
 */
template <unsigned int height>
double dot (const Vector<height>& lhs, const Vector<height>& rhs) {
    double dot_product = 0.0;
    for (int row = 0; row < height; row++) {
        dot_product += lhs[row] * rhs[row];
    }
    return dot_product;
}

/**
 * @brief Calculates the cross product between two given 3 dimensional vectors.
 *
 * @param lhs The vector on the left hand side of the equation.
 * @param rhs The vector on the right hand size of the equation.
 */
#define cross(lhs, rhs) \
    {{ \
        lhs[1] * rhs[2] - lhs[2] * rhs[1], \
        lhs[2] * rhs[0] - lhs[0] * rhs[2], \
        lhs[0] * rhs[1] - lhs[1] * rhs[0], \
    }}

/**
 * @brief Calculates the length - or magnitude - of the given vector.
 *
 * @tparam height The vector's size.
 * @param v
 * @return double The vector's length.
 */
template <unsigned int height>
double length (Vector<height> v) {
    return sqrtf(dot(v, v));
}

/**
 * @brief Calculates the length - or magnitude - squared of the given vector.
 *
 * @tparam height The vector's size.
 * @param v
 * @return double The vector's length squared.
 */
template <unsigned int height>
double length_squared(Vector<height> v) {
    return dot(v, v);
}

/**
 * @brief Calculates a unit vector with the same direction of the given vector.
 *
 * @tparam height The vector's size.
 * @param v
 * @return Vector<height> A unit vector.
 */
template <unsigned int height>
Vector<height> unit (const Vector<height>& v) {
    return v / length(v);
}

/**
 * @brief Reflects a given vector off some given surface.
 *
 * @tparam height The vector's size.
 * @param vector The vector to be reflected.
 * @param surface_normal The surface normal the vector is reflecting off.
 * @return Vector<height> The reflected vector.
 */
template <unsigned int height>
Vector<height> reflect (const Vector<height>& vector, const Vector<height>& surface_normal) {
    Vector<height> normal = unit(surface_normal);
    return vector - 2 * dot(vector, normal) * normal;
}

/**
 * @brief Refracts a given vector through some material.
 *
 * @tparam height The vector's size.
 * @param vector The vector to be refracted.
 * @param surface_normal The surface normal the vector is refracting through.
 * @param refractive_index The refractive index of the material the vector is refracting through.
 * @return Vector<height> The refracted vector.
 */
template <unsigned int height>
Vector<height> refract (const Vector<height>& vector, const Vector<height>& surface_normal, const double refractive_index) {

    Vector<height> v = unit(vector);
    Vector<height> n = unit(surface_normal);

    double cos_theta = dot((Vector<3>)(-1.0 * v), n);
    Vector<3> normal_orthogonal = refractive_index * (v + cos_theta * n);
    Vector<3> normal_parallel = -1.0 * sqrt(fabs(1.0 - length_squared(normal_orthogonal))) * n;

    return normal_orthogonal + normal_parallel;
}

using Point = Vector<3>;

#endif