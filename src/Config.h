#pragma once

namespace Config {
    constexpr int WINDOW_WIDTH = 1600;
    constexpr int WINDOW_HEIGHT = 900;
    constexpr const char* TITLE = "Quantum Fractal Engine [RTX Optimized]";

    // Simulation Resolution (Texture Size)
    constexpr int SIM_RES = 1024; 
    
    // Terrain Mesh Resolution
    constexpr int TERRAIN_RES = 512;

    // Compute Shader Workgroup Size
    constexpr int WORKGROUP_SIZE = 32; 
}