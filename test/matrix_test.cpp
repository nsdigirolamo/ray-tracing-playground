#include "lib/catch2/catch.hpp"
#include "matrix.hpp"
#include "test/test_utils.hpp"

TEST_CASE ("matrix initializers initialize properly") {

    SECTION ("matrix initializes with the default initializer") {
        GIVEN ("a matrix is initialized with the default initializer") {
            WHEN ("the matrix is initialized") {

                Matrix<3, 3> matrix;

                THEN ("all values in the matrix are zero") {

                    for (int row = 0; row < 3; row++) {
                        for (int col = 0; col < 3; col++) {
                            CHECK(matrix[row, col] == 0.0);
                        }
                    }

                }
            }
        }
    }

    SECTION ("array initializer initializes properly") {
        GIVEN ("a matrix is initialized with an array") {
            WHEN ("the matrix is initialized") {

                double my_array[3][3] = {
                    {1.0, 2.0, 3.0},
                    {4.0, 5.0, 6.0},
                    {7.0, 8.0, 9.0}
                };

                Matrix<3, 3> matrix { my_array };

                THEN ("the matrix's values match the values of the array") {

                    for (int row = 0; row < 3; row++) {
                        for (int col = 0; col < 3; col++) {
                            CHECK(matrix[row, col] == my_array[row][col]);
                        }
                    }

                } AND_THEN ("the matrix can be changed without changing the array") {

                    matrix[0, 0] = 100.0;
                    CHECK_FALSE(matrix[0, 0] == my_array[0][0]);

                } AND_THEN ("the array can be changed without changing the matrix") {

                    my_array[0][1] = 100.0;
                    CHECK_FALSE(matrix[1, 0] == my_array[0][1]);

                }
            }
        }
    }
}

TEST_CASE ("matrices sum properly") {

    SECTION ("+= operator sums and then assigns") {
        GIVEN ("two matrices to be summed") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> rhs = {{
                {2, 3, 4},
                {5, 6, 7},
                {8, 9, 10}
            }};

            WHEN ("the += operator is used") {

                lhs += rhs;

                THEN ("the two are summed and the left side is reassigned to the sum") {

                    Matrix<3, 3> sum = {{
                        {3, 5, 7},
                        {9, 11, 13},
                        {15, 17, 19}
                    }};

                    compare_matrix(lhs, sum);
                }
            }
        }
    }

    SECTION ("+ operator sums") {
        GIVEN ("two matrices to be summed") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> rhs = {{
                {2, 3, 4},
                {5, 6, 7},
                {8, 9, 10}
            }};

            WHEN ("the + operator is used") {

                Matrix<3, 3> result = lhs + rhs;

                THEN ("the resulting matrix is the sum of the two") {

                    Matrix<3, 3> sum = {{
                        {3, 5, 7},
                        {9, 11, 13},
                        {15, 17, 19}
                    }};

                    compare_matrix(result, sum);
                }
            }
        }
    }
}

TEST_CASE ("matrices subtract properly") {

    SECTION ("-= operator subtracts and then assigns") {
        GIVEN ("two matrices to be subtracted") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> rhs = {{
                {9, 8, 7},
                {6, 5, 4},
                {3, 2, 1}
            }};

            WHEN ("the -= operator is used") {

                lhs -= rhs;

                THEN ("the two are subtracted and the left side reassigned") {

                    Matrix<3, 3> diff = {{
                        {-8, -6, -4},
                        {-2, 0, 2},
                        {4, 6, 8}
                    }};

                    compare_matrix(lhs, diff);
                }
            }
        }
    }

    SECTION ("- operator subtracts") {
        GIVEN ("two matrices to be subtracted") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> rhs = {{
                {9, 8, 7},
                {6, 5, 4},
                {3, 2, 1}
            }};

            WHEN ("the - operator is used") {

                Matrix<3, 3> result = lhs - rhs;

                THEN ("the resulting matrix is the difference of the two") {

                    Matrix<3, 3> diff = {{
                        {-8, -6, -4},
                        {-2, 0, 2},
                        {4, 6, 8}
                    }};

                    compare_matrix(result, diff);
                }
            }
        }
    }
}

TEST_CASE ("matrices scale properly") {

    SECTION ("*= operator multiplies and then assigns") {
        GIVEN ("a matrix and scalar to be multiplied") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            double scalar = 2;

            WHEN ("the *= operator is used") {

                lhs *= scalar;

                THEN ("the matrix is multipled by the scalar and then the matrix is reassigned") {

                    Matrix<3, 3> product = {{
                        {2, 4, 6},
                        {8, 10, 12},
                        {14, 16, 18}
                    }};

                    compare_matrix(lhs, product);
                }
            }
        }
    }

    SECTION ("* operator multiplies") {
        GIVEN ("a matrix and scalar to be multiplied") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            double scalar = 2;

            WHEN ("the * operator is used") {

                Matrix<3, 3> result = lhs * scalar;

                THEN ("the matrix is multiplied by the scalar") {

                    Matrix<3, 3> product = {{
                        {2, 4, 6},
                        {8, 10, 12},
                        {14, 16, 18}
                    }};

                    compare_matrix(result, product);
                }
            }
        }
    }

    SECTION ("/= operator divides and then assigns") {
        GIVEN ("a matrix and scalar to be divided") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            double scalar = 2;

            WHEN ("the / operator is used") {

                lhs /= scalar;

                THEN ("the matrix is divided by the scalar and then the matrix is reassigned") {

                    Matrix<3, 3> quotient = {{
                        {0.5, 1, 1.5},
                        {2, 2.5, 3},
                        {3.5, 4, 4.5}
                    }};

                    compare_matrix(lhs, quotient);
                }
            }
        }
    }

    SECTION ("/ operator divides") {
        GIVEN ("a matrix and scalar to be divided") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            double scalar = 2;

            WHEN ("the /= operator is used") {

                Matrix<3, 3> result = lhs / scalar;

                THEN ("the matrix is divided by the scalar") {

                    Matrix<3, 3> quotient = {{
                        {0.5, 1, 1.5},
                        {2, 2.5, 3},
                        {3.5, 4, 4.5}
                    }};

                    compare_matrix(result, quotient);
                }
            }
        }
    }

    SECTION ("the hadamard product multiplies") {
        GIVEN ("two matrices to be multiplied") {

            Matrix<3, 3> lhs = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> rhs = {{
                {3, 2, 1},
                {6, 5, 4},
                {9, 8, 7}
            }};

            WHEN ("the hadamard product is used") {

                Matrix<3, 3> result = hadamard(lhs, rhs);

                THEN ("the two matrices are multiplied element-wise") {

                    Matrix<3, 3> product = {{
                        {3, 4, 3},
                        {24, 25, 24},
                        {63, 64, 63}
                    }};

                    compare_matrix(result, product);
                }
            }
        }
    }
}

TEST_CASE ("matrices compare properly") {

    SECTION ("== operator tests equality") {
        GIVEN ("two matrices with matching values") {

            Matrix<3, 3> m1 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> m2 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            WHEN ("the == operator is used") {
                THEN ("true is returned") {
                    CHECK(m1 == m2);
                }
            }
        } AND_GIVEN ("two matrices with non-matching values") {

            Matrix<3, 3> m1 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> m2;

            WHEN ("the == operator is used") {
                THEN ("false is returned") {
                    CHECK_FALSE(m1 == m2);
                }
            }
        }
    }

    SECTION ("!= operator tests inequality") {
        GIVEN ("two matrices with matching values") {

            Matrix<3, 3> m1 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> m2 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            WHEN ("the != operator is used") {
                THEN ("false is returned") {
                    CHECK_FALSE(m1 != m2);
                }
            }
        } AND_GIVEN ("two matrices with non-matching values") {

            Matrix<3, 3> m1 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> m2;

            WHEN ("the != operator is used") {
                THEN ("true is returned") {
                    CHECK(m1 != m2);
                }
            }
        }
    }

    SECTION ("isApprox function tests equality") {
        GIVEN ("two matrices with matching values") {

            Matrix<3, 3> m1 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> m2 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            WHEN ("the isApprox function is used") {
                THEN ("true is returned") {
                    CHECK(isApprox(m1, m2));
                }
            }
        } AND_GIVEN ("two matrices with non-matching values") {

            Matrix<3, 3> m1 = {{
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
            }};

            Matrix<3, 3> m2= {{
                {1.01, 2.01, 3.01},
                {4.01, 5.01, 6.01},
                {7.01, 8.01, 9.01}
            }};;

            WHEN ("the isApprox function is used") {
                THEN ("false is returned") {
                    CHECK_FALSE(isApprox(m1, m2));
                }
            }
        } AND_GIVEN ("two matrices with almost matching values") {

            Matrix<3, 3> m1 = {{
                {1.00001, 2.00001, 3.00001},
                {4.00001, 5.00001, 6.00001},
                {7.00001, 8.00001, 9.00001}
            }};

            Matrix<3, 3> m2 = {{
                {1.00, 2.00, 3.00},
                {4.00, 5.00, 6.00},
                {7.00, 8.00, 9.00}
            }};

            WHEN ("the isApprox function is used") {
                THEN ("true is returned") {
                    CHECK(isApprox(m1, m2));
                }
            }
        }
    }
}
