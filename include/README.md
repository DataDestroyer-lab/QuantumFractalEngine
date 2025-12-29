# QuantumFractalEngine

QuantumFractalEngine is a high-performance C++ rendering engine combining procedural fractal terrain generation, quantum field simulations, and real-time physics using OpenGL 4.6 and Compute Shaders.

## Features

*   **Procedural Terrain**: Infinite terrain generation using Fractal Brownian Motion (FBM) noise with dynamic patching.
*   **Physics Simulation**: GPU-accelerated physics using Compute Shaders.
*   **Quantum Field Simulation**: Visual simulation of quantum probability fields (supports CUDA acceleration if enabled).
*   **Dynamic Weather**: Rain particle system with wind influence and puddle accumulation.
*   **Magnetic Field Visualization**: Interactive magnetic field visualization with vector field arrows.
*   **Real-time Editor**: Integrated ImGui interface for tweaking simulation parameters, weather, and visual settings on the fly.
*   **Day/Night Cycle**: Dynamic sky and lighting adjustments.

## Prerequisites

*   **C++ Compiler**: C++17 compliant (MSVC, GCC, Clang).
*   **CMake**: Version 3.14 or higher.
*   **OpenGL**: Graphics card supporting OpenGL 4.6.
*   **Git**: For fetching dependencies.

## Build Instructions

The project uses CMake for build configuration. Dependencies (GLFW, GLM, ImGui) are automatically fetched via CMake's `FetchContent`.

1.  **Clone the repository:**
    ```bash
    git clone <repository-url>
    cd QuantumFractalEngine
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the project:**
    ```bash
    cmake ..
    ```

4.  **Build:**
    ```bash
    cmake --build . --config Release
    ```

# QuantumFractalEngine

QuantumFractalEngine is a compact C++ real-time engine demo featuring procedurally generated fractal terrain, a simple GPU-accelerated physics pass, a visual quantum field effect, weather, and an integrated ImGui-based editor.

This repository contains a small self-contained engine intended for experimentation and learning — it is not a production game engine.

## Highlights

- Procedural terrain using seeded FBM noise (sphere + infinite planar patches).
- GPU-driven height/velocity map (compute shader) for simple physics interactions.
- ImGui editor with live controls: terrain parameters, physics, weather, magnetic field, spawnable objects, and more.
- Magnetic field preview with arrow visualization and editable gizmo.
- Day/night cycle, rain particles, and configurable visual palette.

## Quick Start (Windows)

1. Clone the repo:

```powershell
git clone <repo-url>
cd QuantumFractalEngine
```

2. Configure & build (Debug recommended while developing):

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

3. Run the executable (from repo root):

```powershell
build\\Debug\\QuantumFractalEngine.exe
```

Make sure the `assets/` folder is present in the working directory.

## Controls

- W/A/S/D: Move camera
- Space / Left Shift: Move up / down
- Mouse: Look (when mouse capture is enabled)
- Tab: Toggle mouse capture
- H: Toggle help overlay
- ImGui: Use the Editor window to change parameters, spawn objects, focus actors, and drag the magnetic gizmo.

## Editor Tips

- The Editor panel (ImGui) appears at startup. If it is not visible, ensure `assets/config.json` does not set `captureMouse` to true.
- Use the Outliner to select and focus spawned objects.
- Toggle "Enable Magnetic Gizmo Drag" and click the gizmo in the viewport to move the magnetic center.

## Configuration

Persistent settings are stored in `assets/config.json`. The Editor's "Save Config" button writes current settings back to that file.

Important editable groups:
- Terrain: `seed`, `octaves`, `frequency`, `scale`, `infinite` toggle, chunk size, grid resolution.
- Physics: `gravity`, `timeStep`.
- Visual: clear color, terrain palette (low/mid/high), wireframe.
- Simulation: time scale and subsystem toggles.

## Development notes

- The project uses CMake + FetchContent for dependencies (GLFW, GLM, ImGui). Ensure network access during initial configure.
- Shaders live in the `shaders/` folder and can be edited and recompiled by rebuilding.

## Commit & Push (example)

After updating the README, commit and push to your remote (`origin`) as follows:

```powershell
git add include/README.md
git commit -m "docs: update README with build/run instructions and editor tips"
git push origin main
```

Replace `main` with your default branch name if different.

## License

This project does not include a license file. Add one if you intend to publish.

## Contact

Open an issue in the repository for questions, feature requests, or problems building.

Enjoy experimenting!
