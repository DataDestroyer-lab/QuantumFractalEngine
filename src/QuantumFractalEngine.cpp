#include "QuantumEngine.h"
#include "Config.h"

#ifdef ENABLE_CUDA
#include <cuda_gl_interop.h>
#include <cuda_runtime.h>
extern "C" void launchQuantumKernel(float4* field, int width, int height, float time);
#endif

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
    cudaGraphicsGLRegisterBuffer((cudaGraphicsResource_t*)&cudaResource, pbo, cudaGraphicsMapFlagsWriteDiscard);
#else
    computeShader = new Shader("shaders/quantum.comp");
    glBindImageTexture(1, textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
#endif
}

QuantumEngine::~QuantumEngine() {
#ifdef ENABLE_CUDA
    if (cudaResource) {
        cudaGraphicsUnregisterResource((cudaGraphicsResource_t)cudaResource);
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
    cudaGraphicsMapResources(1, (cudaGraphicsResource_t*)&cudaResource, 0);
    cudaGraphicsResourceGetMappedPointer((void**)&d_ptr, &bytes, (cudaGraphicsResource_t)cudaResource);
    
    // Launch Kernel
    launchQuantumKernel(d_ptr, Config::SIM_RES, Config::SIM_RES, totalTime);
    
    // Unmap
    cudaGraphicsUnmapResources(1, (cudaGraphicsResource_t*)&cudaResource, 0);

    // Copy PBO to Texture
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Config::SIM_RES, Config::SIM_RES, GL_RGBA, GL_FLOAT, 0);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
#else
    computeShader->use();
    computeShader->setFloat("dt", dt);
    glDispatchCompute(Config::SIM_RES / 32, Config::SIM_RES / 32, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
#endif
}