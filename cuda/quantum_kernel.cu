#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>

// Macro for CUDA error checking in kernels
#define CudaCheckError() {                                                                         \
    cudaError_t err = cudaGetLastError();                                                          \
    if (err != cudaSuccess) {                                                                      \
        fprintf(stderr, "CUDA error in %s:%d: %s\n", __FILE__, __LINE__, cudaGetErrorString(err)); \
        /* Optionally, you might want to exit or throw an exception here */                        \
    }                                                                                              \
}

// Basic CUDA kernel for quantum probability field calculation
__global__ void quantumKernel(float4* field, int width, int height, float time) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height) return;

    int idx = y * width + x;
    
    // Placeholder quantum wave function simulation
    float u = (float)x / width;
    float v = (float)y / height;
    
    float val = sinf(u * 10.0f + time) * cosf(v * 10.0f + time);
    // Store probability in Z (Blue) channel, initialize others to avoid garbage
    field[idx] = make_float4(0.0f, 0.0f, val * val, 1.0f);
}

extern "C" void launchQuantumKernel(float4* field, int width, int height, float time) {
    dim3 blockSize(16, 16);
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (height + blockSize.y - 1) / blockSize.y);
    
    quantumKernel<<<gridSize, blockSize>>>(field, width, height, time);
}