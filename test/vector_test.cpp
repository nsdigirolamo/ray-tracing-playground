#include "lib/catch2/catch.hpp"
#include "vector.hpp"
#include "test/test_utils.hpp"

TEST_CASE ("vector initializers initialize properly") {

    SECTION ("vector initializes with the default initializer") {
        GIVEN ("a vector is initialized with the default initializer") {
            WHEN ("the vector is initialized") {

                Vector<3> vector;

                THEN ("all values in the matrix are zero") {

                    for (int row = 0; row < 3; row++) {
                        CHECK(vector[row] == 0.0);
                    }
                }
            } 
        }
    }

    SECTION ("array initializer initializes properly") {
        GIVEN ("a vector is initialized with an array") {
            WHEN ("the vector is initialized") {

                double my_array[3] = {1.0, 2.0, 3.0};

                Vector<3> vector { my_array };

                THEN ("the vector's values match the values of the array") {

                    for (int row = 0; row < 3; row++) {
                        CHECK(vector[row] == my_array[row]);
                    }

                } AND_THEN ("the vector can be changed without changing the array") {

                    vector[0] = 100.0;
                    CHECK_FALSE(vector[0] == my_array[0]);

                } AND_THEN ("the array can be changed without changing the vector") {

                    my_array[1] = 100.0;
                    CHECK_FALSE(vector[1] == my_array[1]);

                }
            }
        }
    }
}

TEST_CASE ("vector dot product") {

    SECTION ("dot product") {
        GIVEN ("two vectors") {

            Vector<3> v1 = {{1, 2, 3}};
            Vector<3> v2 = {{7, 8, 9}};

            WHEN ("the dot function is used") {

                double result = dot(v1, v2);

                THEN ("the dot product is calculated") {

                    double dot_product = 50;

                    CHECK(result == dot_product);
                }
            }
        }
    }
}

TEST_CASE ("length of vector") {

    SECTION ("length") {
        GIVEN ("a vector") {

            Vector<3> vector = {{1, 2, 3}};

            WHEN ("the length function is used") {

                double result = vector.length();

                THEN ("the length is calculated") {

                    double length = sqrt(14);

                    CHECK(result == Approx(length));
                }
            }
        } AND_GIVEN ("a unit vector") {

            Vector<3> unit_vector = {{1, 0, 0}};

            WHEN ("the length function is used") {

                double result = unit_vector.length();

                THEN ("the length is calculated as one") {

                    double length = 1.0;

                    CHECK(result == length);
                }
            }
        }
    }
}

TEST_CASE ("direction of vector") {

    SECTION ("direction") {
        GIVEN ("a vector") {

            Vector<3> vector = {{1, 2, 3}};

            WHEN ("the direction function is used") {

                Vector<3> result = vector.direction();

                THEN ("the length is calculated") {

                    Vector<3> direction = {{0.26726, 0.53452, 0.80178}};

                    compare_matrix(result, direction);
                }
            }
        } AND_GIVEN ("a unit vector") {

            Vector<3> unit_vector = {{1, 0, 0}};

            WHEN ("the direction function is used") {

                Vector<3> result = unit_vector.direction();

                THEN ("the direction is equal to the unit vector") {

                    compare_matrix(result, unit_vector);
                }
            }
        }
    }
}