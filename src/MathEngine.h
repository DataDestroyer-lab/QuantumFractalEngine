#pragma once
#include <glm/glm.hpp>
#include <random>

class MathEngine {
public:
    static void Init();
    static float RandomFloat(float min, float max);
private:
    static std::mt19937 s_Gen;
};