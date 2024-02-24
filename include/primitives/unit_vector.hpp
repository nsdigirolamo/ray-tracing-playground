#ifndef UNIT_VECTOR_HPP
#define UNIT_VECTOR_HPP

#include "primitives/vector.hpp"

/**
 * @brief A Vector with a dimension - or magnitude - equal to 1.
 *
 * @tparam height The size of the Unit Vector.
 */
template <unsigned int height>
requires (0 < height)
class UnitVector: public Vector<height> {

    public:

        /**
         * @brief Constructs a new Unit Vector where all values are 0, except
         * for the first value.
         */
        UnitVector () {
            for (int row = 0; row < height; ++row) {
                this->values[row][0] = 0.0;
            }
            this->values[0][0] = 1.0;
        }

        /**
         * @brief Constructs a new Unit Vector object where the elements of the
         * Unit Vector are the same as the given Vector.
         *
         * @param v
         */
        UnitVector (const Vector<height>& v) {
            Vector<height> unit_v = unit(v);
            for (int row = 0; row < height; ++row) {
                this->values[row][0] = unit_v[row];
            }
        }

        /**
         * @brief Constructs a new Unit Vector object where the elements of the
         * Unit Vector are the same as the given array.
         */
        UnitVector (const double (&values)[height])
            : UnitVector((Vector<height>)(values))
        { }

        /**
         * @brief Constructs a new Unit Vector object where the elements of the
         * Unit Vector are the same as the given Matrix.
         *
         * @param m
         */
        UnitVector (const Matrix<height, 1>& m)
            : UnitVector((Vector<height>)(m))
        { }
};

#endif