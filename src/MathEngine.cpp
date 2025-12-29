#include "MathEngine.h"

std::mt19937 MathEngine::s_Gen;

void MathEngine::Init() {
    std::random_device rd;
    s_Gen.seed(rd());
}

float MathEngine::RandomFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(s_Gen);
}