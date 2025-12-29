#pragma once
#include "Shader.h"

class PhysicsEngine {
public:
    void Init();
    ~PhysicsEngine(); // Destructor for resource cleanup
    void Update(float dt);
    unsigned int GetHeightMap() const { return textureID; }
private:
    Shader* computeShader = nullptr;
    unsigned int textureID = 0;
};