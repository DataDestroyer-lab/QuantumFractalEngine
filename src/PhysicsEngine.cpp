// PhysicsEngine implementation
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "PhysicsEngine.h"
#include "Config.h"
#include <iostream>

PhysicsEngine::PhysicsEngine() {}

void PhysicsEngine::Init() {
    computeShader = new Shader("shaders/physics.comp");

    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // RG32F: R=Height, G=Velocity
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, Config::SIM_RES, Config::SIM_RES, 0, GL_RG, GL_FLOAT, NULL);

    glBindImageTexture(0, textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RG32F);
}

// Destructor to clean up allocated resources
PhysicsEngine::~PhysicsEngine() {
    if (computeShader) delete computeShader;
    if (textureID) glDeleteTextures(1, &textureID);
}

void PhysicsEngine::Update(float dt) {
    computeShader->use();
    computeShader->setFloat("dt", dt);
    glBindImageTexture(0, textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RG32F);
    glDispatchCompute(Config::SIM_RES / 32, Config::SIM_RES / 32, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}