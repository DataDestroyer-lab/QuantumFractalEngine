// TerrainEngine implementation
#include <glad/glad.h>
#include "TerrainEngine.h"
#include "Config.h"
#include <vector>

TerrainEngine::TerrainEngine() {}

void TerrainEngine::Init() {
    shader = new Shader("shaders/terrain.vert", "shaders/terrain.frag");
    generateMesh();
}

TerrainEngine::~TerrainEngine() {
    if (shader) delete shader;
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);
}

void TerrainEngine::generateMesh() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int res = Config::TERRAIN_RES;

    for(int z=0; z<res; ++z) {
        for(int x=0; x<res; ++x) {
            vertices.push_back((float)x / (res-1)); // X
            vertices.push_back(0.0f);               // Y
            vertices.push_back((float)z / (res-1)); // Z
            vertices.push_back((float)x / (res-1)); // U
            vertices.push_back((float)z / (res-1)); // V
        }
    }
    
    for(int z=0; z<res-1; ++z) {
        for(int x=0; x<res-1; ++x) {
            int tl = z*res + x;
            int tr = tl + 1;
            int bl = (z+1)*res + x;
            int br = bl + 1;
            indices.push_back(tl); indices.push_back(bl); indices.push_back(tr);
            indices.push_back(tr); indices.push_back(bl); indices.push_back(br);
        }
    }
    indexCount = indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void TerrainEngine::Render(const glm::mat4& view, const glm::mat4& proj, unsigned int physTex, unsigned int quantTex) {
    shader->use();
    shader->setMat4("view", view);
    shader->setMat4("projection", proj);
    
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, physTex);
    shader->setInt("physicsMap", 0);
    
    glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, quantTex);
    shader->setInt("quantumMap", 1);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}