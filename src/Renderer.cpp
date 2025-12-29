#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(GLFWwindow* win) : window(win) {}

// Initialize static members
bool Renderer::firstMouse = true;
float Renderer::lastX = Config::WINDOW_WIDTH / 2.0f;
float Renderer::lastY = Config::WINDOW_HEIGHT / 2.0f;
Renderer* Renderer::instance = nullptr;

// Camera Class Implementation
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), MouseSensitivity(0.1f) {
    Position = position;
    Up = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(int direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == GLFW_KEY_W)
        Position += Front * velocity;
    if (direction == GLFW_KEY_S)
        Position -= Front * velocity;
    if (direction == GLFW_KEY_A)
        Position -= glm::normalize(glm::cross(Front, Up)) * velocity;
    if (direction == GLFW_KEY_D)
        Position += glm::normalize(glm::cross(Front, Up)) * velocity;
    if (direction == GLFW_KEY_SPACE)
        Position += Up * velocity;
    if (direction == GLFW_KEY_LEFT_SHIFT)
        Position -= Up * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
}

// Renderer Class Implementation
Renderer::Renderer(GLFWwindow* win) : window(win), camera(glm::vec3(0.5f, 1.0f, 1.5f)) {
    instance = this; // Set the singleton instance
}

void Renderer::Init() {
    glEnable(GL_DEPTH_TEST);
    physics.Init();
    quantum.Init();
    terrain.Init();
}

void Renderer::processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (instance) { // Ensure instance exists before accessing camera
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) instance->camera.ProcessKeyboard(GLFW_KEY_W, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) instance->camera.ProcessKeyboard(GLFW_KEY_S, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) instance->camera.ProcessKeyboard(GLFW_KEY_A, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) instance->camera.ProcessKeyboard(GLFW_KEY_D, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) instance->camera.ProcessKeyboard(GLFW_KEY_SPACE, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) instance->camera.ProcessKeyboard(GLFW_KEY_LEFT_SHIFT, deltaTime);
    }
}

void Renderer::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (instance) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;
        instance->camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

void Renderer::RenderFrame(float dt) {
    // 1. Compute Pass
    physics.Update(dt);
    quantum.Update(dt);

    // 2. Render Pass
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)Config::WINDOW_WIDTH / (float)Config::WINDOW_HEIGHT, 0.01f, 100.0f);

    terrain.Render(view, proj, physics.GetHeightMap(), quantum.GetFieldTexture());
    
    glfwSwapBuffers(window);
}