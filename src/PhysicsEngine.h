// PhysicsEngine: handles simulation steps (compute shaders or CUDA)
#pragma once
#include "Shader.h"

class PhysicsEngine {
public:
    PhysicsEngine();
    ~PhysicsEngine();

    void Init();
    void Update(float dt);
    unsigned int GetHeightMap() const { return textureID; }
private:
    Shader* computeShader = nullptr;
    unsigned int textureID = 0;
};