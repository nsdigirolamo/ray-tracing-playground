#ifndef UNIT_VECTOR_HPP
#define UNIT_VECTOR_HPP

#include "primitives/vector.hpp"

template <unsigned int height>
requires (0 < height)
class UnitVector: public Vector<height> {

    public:

        UnitVector () {
            for (int row = 0; row < height; ++row) {
                this->values[row][0] = 0.0;
            }
            this->values[0][0] = 1.0;
        }

        UnitVector (const Vector<height>& v) {
            Vector<height> unit_v = unit(v);
            for (int row = 0; row < height; ++row) {
                this->values[row][0] = unit_v[row];
            }
        }

        UnitVector (const double (&values)[height])
            : UnitVector((Vector<height>)(values))
        { }

        UnitVector (const Matrix<height, 1>& m) 
            : UnitVector((Vector<height>)(m))
        { }
};

#endif