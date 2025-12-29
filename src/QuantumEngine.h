#pragma once
#include "Shader.h"

class QuantumEngine {
public:
    void Init();
    ~QuantumEngine(); // Destructor for resource cleanup
    void Update(float dt);
    unsigned int GetFieldTexture() const { return textureID; }
private:
    Shader* computeShader = nullptr;
    unsigned int textureID = 0;
    unsigned int pbo = 0;
    void* cudaResource = nullptr;
    float totalTime = 0.0f;
};