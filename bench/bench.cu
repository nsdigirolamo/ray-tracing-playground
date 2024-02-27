#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cuda.h>
#include <iostream>

#include "lib/doctest/doctest.hpp"
#include "lib/nanobench/nanobench.h"
#include "primitives/matrix.hpp"
#include "random_utils.hpp"
#include "test/test_utils.hpp"

#define HEIGHT 256
#define WIDTH 256

#define SIZE sizeof(Matrix<HEIGHT, WIDTH>)

__global__ void add (Matrix<HEIGHT, WIDTH>* sum, Matrix<HEIGHT, WIDTH>* lhs, Matrix<HEIGHT, WIDTH>* rhs) {

    int row = (blockIdx.y * blockDim.y) + threadIdx.y;
    int col = (blockIdx.x * blockDim.y) + threadIdx.x;

    (*sum)[row][col] = (*lhs)[row][col] + (*rhs)[row][col];
}

TEST_CASE("Compare Addition") {

    Matrix<HEIGHT, WIDTH> host_lhs;
    Matrix<HEIGHT, WIDTH> host_rhs;

    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            host_lhs[row][col] = randomDouble();
            host_rhs[row][col] = randomDouble();
        }
    }

    Matrix<HEIGHT, WIDTH> host_sum;
    Matrix<HEIGHT, WIDTH> empty_host_sum;

    // Device Memory

    Matrix<HEIGHT, WIDTH>* device_lhs;
    Matrix<HEIGHT, WIDTH>* device_rhs;

    cudaMalloc(&device_lhs, SIZE);
    cudaMemcpy(device_lhs, &host_lhs, SIZE, cudaMemcpyHostToDevice);

    cudaMalloc(&device_rhs, SIZE);
    cudaMemcpy(device_rhs, &host_rhs, SIZE, cudaMemcpyHostToDevice);

    Matrix<HEIGHT, WIDTH>* device_sum;

    cudaMalloc(&device_sum, SIZE);
    cudaMemcpy(device_sum, &host_sum, SIZE, cudaMemcpyHostToDevice);

    dim3 grid_dims(8, 8);
    dim3 block_dims(32, 32);

    // Benchmark

    ankerl::nanobench::Bench b;

    b.minEpochIterations(1000).run("Serial + Operation", [&] {

        host_sum = host_lhs + host_rhs;

    });

    b.minEpochIterations(1000).run("Parallel + Operation", [&] {

        add<<<grid_dims, block_dims>>>(device_sum, device_lhs, device_rhs);
        cudaDeviceSynchronize();

    });

    cudaMemcpy(&empty_host_sum, device_sum, SIZE, cudaMemcpyDeviceToHost);

    CHECK_MATRIX(host_sum, empty_host_sum);
}
