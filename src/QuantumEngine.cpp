// QuantumEngine implementation
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "QuantumEngine.h"
#include "Config.h"
#include <cstdio>
#include <cstdlib>

#ifdef ENABLE_CUDA
#include <cuda_gl_interop.h>
#include <cuda_runtime.h>
// Macro for CUDA API error checking
#define CUDA_CHECK(call)                                                                           \
    do {                                                                                           \
        cudaError_t err = call;                                                                    \
        if (err != cudaSuccess) {                                                                  \
            fprintf(stderr, "CUDA error in %s:%d: %s\n", __FILE__, __LINE__, cudaGetErrorString(err)); \
            exit(EXIT_FAILURE); /* Or handle more gracefully */                                    \
        }                                                                                          \
    } while (0)
extern "C" void launchQuantumKernel(float4* field, int width, int height, float time);
#endif

QuantumEngine::QuantumEngine() {}

void QuantumEngine::Init() {
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // RGBA32F: Real, Imag, Probability, Unused
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, Config::SIM_RES, Config::SIM_RES, 0, GL_RGBA, GL_FLOAT, NULL);
    
#ifdef ENABLE_CUDA
    // Create Pixel Buffer Object for CUDA Interop
    glGenBuffers(1, &pbo);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, Config::SIM_RES * Config::SIM_RES * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    // Register PBO with CUDA
    CUDA_CHECK(cudaGraphicsGLRegisterBuffer((cudaGraphicsResource_t*)&cudaResource, pbo, cudaGraphicsMapFlagsWriteDiscard));
#else
    computeShader = new Shader("shaders/quantum.comp");
    glBindImageTexture(1, textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
#endif
}

QuantumEngine::~QuantumEngine() {
#ifdef ENABLE_CUDA
    if (cudaResource) {
        CUDA_CHECK(cudaGraphicsUnregisterResource((cudaGraphicsResource_t)cudaResource));
    }
    if (pbo) {
        glDeleteBuffers(1, &pbo);
    }
#else
    if (computeShader) delete computeShader;
#endif
    if (textureID) glDeleteTextures(1, &textureID);
}

void QuantumEngine::Update(float dt) {
    totalTime += dt;

#ifdef ENABLE_CUDA
    float4* d_ptr;
    size_t bytes;
    
    // Map PBO to get CUDA device pointer
    CUDA_CHECK(cudaGraphicsMapResources(1, (cudaGraphicsResource_t*)&cudaResource, 0));
    CUDA_CHECK(cudaGraphicsResourceGetMappedPointer((void**)&d_ptr, &bytes, (cudaGraphicsResource_t)cudaResource));
    
    // Launch Kernel
    launchQuantumKernel(d_ptr, Config::SIM_RES, Config::SIM_RES, totalTime);
    
    // Unmap
    CUDA_CHECK(cudaGraphicsUnmapResources(1, (cudaGraphicsResource_t*)&cudaResource, 0));

    // Copy PBO to Texture
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Config::SIM_RES, Config::SIM_RES, GL_RGBA, GL_FLOAT, 0);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
#else
    computeShader->use();
    computeShader->setFloat("dt", dt);
    glBindImageTexture(1, textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    glDispatchCompute(Config::SIM_RES / 32, Config::SIM_RES / 32, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
#endif
}