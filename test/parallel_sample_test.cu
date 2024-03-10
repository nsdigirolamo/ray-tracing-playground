#include <cuda.h>
#include <iostream>
#include <cmath>

#include "lib/doctest/doctest.hpp"
#include "primitives/matrix.hpp"
#include "random_utils.hpp"
#include "test/test_utils.hpp"
#include "primitives/color.hpp"

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
    
    host_sum = host_lhs + host_rhs;

    add<<<grid_dims, block_dims>>>(device_sum, device_lhs, device_rhs);
    cudaDeviceSynchronize();

    cudaMemcpy(&empty_host_sum, device_sum, SIZE, cudaMemcpyDeviceToHost);

    CHECK_MATRIX(host_sum, empty_host_sum);
}

#define PIXEL_HEIGHT 4
#define PIXEL_WIDTH 4
#define PIXEL_DEPTH 4
#define MULTIPLIER 2

__global__ void multiply (Color* pixels) {

    int row = blockIdx.y;
    int col = blockIdx.x;
    int depth = threadIdx.x;

    pixels[(depth * PIXEL_HEIGHT * PIXEL_WIDTH) + (row * PIXEL_WIDTH) + col] *= MULTIPLIER;
}

TEST_CASE("Testing Unified (Managed) Memory") {

    Color* pixels;
    size_t size = sizeof(Color) * PIXEL_HEIGHT * PIXEL_WIDTH * PIXEL_DEPTH;

    cudaMallocManaged(&pixels, size);

    Color* expected_result = (Color*)(malloc(size));

    for (int row = 0; row < PIXEL_HEIGHT; ++row) {
        for (int col = 0; col < PIXEL_WIDTH; ++col) {
            for (int level = 0; level < PIXEL_DEPTH; ++level) {

                Color val { fabs(randomDouble()), fabs(randomDouble()), fabs(randomDouble()) };
                pixels[(level * PIXEL_HEIGHT * PIXEL_WIDTH) + (row * PIXEL_WIDTH) + col] = val;
                expected_result[(level * PIXEL_HEIGHT * PIXEL_WIDTH) + (row * PIXEL_WIDTH) + col] = val * MULTIPLIER;

            }
        }
    }

    dim3 grid_dims(PIXEL_HEIGHT, PIXEL_WIDTH);
    dim3 block_dims(PIXEL_DEPTH);

    multiply<<<grid_dims, block_dims>>>(pixels);
    cudaDeviceSynchronize();

    for (int row = 0; row < PIXEL_HEIGHT; ++row) {
        for (int col = 0; col < PIXEL_WIDTH; ++col) {
            for (int level = 0; level < PIXEL_DEPTH; ++level) {
                Color actual_pixel = pixels[(level * PIXEL_HEIGHT * PIXEL_WIDTH) + (row * PIXEL_WIDTH) + col];
                Color expected_pixel = expected_result[(level * PIXEL_HEIGHT * PIXEL_WIDTH) + (row * PIXEL_WIDTH) + col];
                CHECK_COLOR(actual_pixel, expected_pixel);
            }
        }
    }
}