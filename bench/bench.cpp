#include "lib/nanobench/nanobench.h"
#include "primitives/matrix.hpp"
#include "random_utils.hpp"

#define HEIGHT 100
#define WIDTH 100

int main () {

    double m[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            m[i][j] = randomDouble();
        }
    }

    Matrix<HEIGHT, WIDTH> matrix1 { m };

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            m[i][j] = randomDouble();
        }
    }

    Matrix<HEIGHT, WIDTH> matrix2 { m };

    ankerl::nanobench::Bench b;

    b.minEpochIterations(5000).run("+= Operation", [&] {

        matrix1 += matrix2;

    });

    b.minEpochIterations(5000).run("+ Operation", [&] {

        Matrix<HEIGHT, WIDTH> matrix3 = matrix1 + matrix2;

    });

}