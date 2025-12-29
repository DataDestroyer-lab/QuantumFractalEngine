// TerrainEngine: procedural terrain generation and mesh management
#pragma once
#include "Shader.h"
#include <vector>
#include <glm/glm.hpp>

class TerrainEngine {
public:
    TerrainEngine();
    ~TerrainEngine();

    void Init();
    void Render(const glm::mat4& view, const glm::mat4& proj, unsigned int physTex, unsigned int quantTex);
private:
    unsigned int VAO = 0, VBO = 0, EBO = 0; // OpenGL object IDs
    int indexCount = 0;                     // Number of indices to draw
    Shader* shader = nullptr;
    void generateMesh();
};