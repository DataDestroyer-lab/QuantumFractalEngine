#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "PhysicsEngine.h"
#include "QuantumEngine.h"
#include "TerrainEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Simple Camera class (could be moved to its own file)
class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(int direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

private:
    void updateCameraVectors();
};

class Renderer {
public:
    Renderer(GLFWwindow* win);
    void Init();
    void RenderFrame(float dt);
    static void processInput(GLFWwindow* window, float deltaTime);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
private:
    GLFWwindow* window;
    PhysicsEngine physics;
    QuantumEngine quantum;
    TerrainEngine terrain;
    Camera camera;

    // Mouse state for camera
    static bool firstMouse;
    static float lastX, lastY;
    static Renderer* instance; // Singleton pattern for static callbacks
};