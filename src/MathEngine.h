// MathEngine: math utilities and helpers (noise, fractal, etc.)
#pragma once

#include <random>

class MathEngine {
public:
    MathEngine();
    ~MathEngine();

    static void Init();
    static float RandomFloat(float min, float max);
private:
    static std::mt19937 s_Gen;
};