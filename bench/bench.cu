#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cuda.h>
#include <iostream>
#include <cmath>

#include "lib/doctest/doctest.hpp"
#include "lib/nanobench/nanobench.h"
#include "primitives/matrix.hpp"
#include "random_utils.hpp"
#include "test/test_utils.hpp"
#include "primitives/color.hpp"

void handleCudaError (cudaError_t e, const char* identifier, bool exits = true) {

    fprintf(stdout, "Checking for error in %s... ", identifier);

	if (e == cudaSuccess) {
        fprintf(stdout, "No Error Found!\n");
        return;
    }

	fprintf(stdout, "%s %s: %s\n",
		identifier,
		cudaGetErrorName(e),
		cudaGetErrorString(e)
	);

	fflush(NULL);

	if (exits) exit(1);
}

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

    /**

    b.minEpochIterations(1000).run("Serial + Operation", [&] {

        host_sum = host_lhs + host_rhs;

    });

    */
    
    host_sum = host_lhs + host_rhs;

    /**

    b.minEpochIterations(1000).run("Parallel + Operation", [&] {

        add<<<grid_dims, block_dims>>>(device_sum, device_lhs, device_rhs);
        cudaDeviceSynchronize();

    });

    */

    add<<<grid_dims, block_dims>>>(device_sum, device_lhs, device_rhs);
    cudaDeviceSynchronize();

    cudaMemcpy(&empty_host_sum, device_sum, SIZE, cudaMemcpyDeviceToHost);

    CHECK_MATRIX(host_sum, empty_host_sum);
}

#define PIXEL_HEIGHT 4
#define PIXEL_WIDTH 4
#define PIXEL_DEPTH 4
#define MULTIPLIER 2

__global__ void multiply (Color* pixels, double multiplier) {

    int row = blockIdx.y;
    int col = blockIdx.x;
    int depth = threadIdx.x;

    pixels[(depth * PIXEL_HEIGHT * PIXEL_WIDTH) + (row * PIXEL_WIDTH) + col] *= 2;
}

TEST_CASE("Testing Unified (Managed) Memory") {

    Color* pixels;
    cudaError_t e;

    const int height = PIXEL_HEIGHT;
    const int width = PIXEL_WIDTH;
    const int depth = PIXEL_DEPTH;
    const double multiplier = MULTIPLIER;

    size_t size = sizeof(Color) * height * width * depth;

    e = cudaMallocManaged(&pixels, size);
    handleCudaError(e, "Managed Malloc");

    Color* expected_result = (Color*)(malloc(size));

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            for (int level = 0; level < depth; ++level) {

                Color val { fabs(randomDouble()), fabs(randomDouble()), fabs(randomDouble()) };
                pixels[(level * height * width) + (row * width) + col] = val;
                std::cout << pixels[(level * height * width) + (row * width) + col] << "\n\n";
                expected_result[(level * height * width) + (row * width) + col] = val * multiplier;

            }
        }
    }

    ankerl::nanobench::Bench b;

    /**

    b.epochIterations(1).run("Pixel 3D Array Multiply", [&] {

        dim3 grid_dims(height, width);
        dim3 block_dims(depth);

        multiply<<<grid_dims, block_dims>>>(pixels, multiplier);

        e = cudaDeviceSynchronize();
        handleCudaError(e, "Synchronize");
    });

    */

    dim3 grid_dims(height, width);
    dim3 block_dims(depth);

    multiply<<<grid_dims, block_dims>>>(pixels, multiplier);

    e = cudaDeviceSynchronize();
    handleCudaError(e, "Synchronize");

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            for (int level = 0; level < depth; ++level) {
                Color actual_pixel = pixels[(level * height * width) + (row * width) + col];
                Color expected_pixel = expected_result[(level * height * width) + (row * width) + col];
                std::cout << actual_pixel << "\n\n";
                CHECK_COLOR(actual_pixel, expected_pixel);
            }
        }
    }
}

/**
__global__ void pitched_array_test (cudaPitchedPtr pitched_ptr) {

    double* elements = (double*)(pitched_ptr.ptr);
    size_t pitch = pitched_ptr.pitch;
    int width = pitched_ptr.xsize;
    int height = pitched_ptr.ysize;

    int row = blockIdx.y;
    int col = blockIdx.x;
    int depth = threadIdx.x;

    double* element = elements + ((depth * height * pitch) + (row * pitch) + col);

    *element *= 2;
}
 *

TEST_CASE("Testing cudaPitchPtr") {

    const int width = 8;
    const int height = 8;
    const int depth = 8;

    double* host_nums = (double*) malloc(sizeof(double) * width * height * depth);
    double* host_result = (double*) malloc(sizeof(double) * width * height * depth);
    double* extra_host_result = (double*) malloc(sizeof(double) * width * height * depth);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            for (int level = 0; level < depth; ++level) {
                int i = level + row + col;
                host_nums[(level * height * width) + (row * width) + col] = i;
                host_result[(level * height * width) + (row * width) + col] = i * 2;
            }
        }
    }

    cudaArray *pixels;

    cudaMalloc3DArray(&pixels, );


    //cudaExtent pixelExtent = make_cudaExtent(sizeof(Color) * width, height, depth);

    //cudaMalloc3D(&pixels, pixelExtent);

    cudaMemcpy3DParms params;

    params.srcPtr = make_cudaPitchedPtr(pixels, sizeof(Color) * width, width, height);


}

*/
