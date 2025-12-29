#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.h"
#include "glad/glad.h" // Include GLAD header
#include "Renderer.h"
#include "MathEngine.h"

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, Config::TITLE, NULL, NULL);
    if(!window) {
        std::cout << "Failed to create window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Disable cursor and capture it
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Renderer::mouse_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    MathEngine::Init();
    {
        Renderer renderer(window);
        renderer.Init();
        std::cout << "Engine Initialized" << std::endl;

        float lastTime = 0.0f;
        while(!glfwWindowShouldClose(window)) {
            float time = (float)glfwGetTime();
            float dt = time - lastTime;
            lastTime = time;

            Renderer::processInput(window, dt); // Process camera input

            renderer.RenderFrame(dt);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}