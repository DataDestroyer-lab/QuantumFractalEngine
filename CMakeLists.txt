cmake_minimum_required(VERSION 3.14)
project(QuantumFractalEngine)

set(CMAKE_CXX_STANDARD 17)

# --- Optional CUDA Support ---
include(CheckLanguage)
check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
    message(STATUS "CUDA Compiler found: ${CMAKE_CUDA_COMPILER}")
    enable_language(CUDA)
    find_package(CUDAToolkit REQUIRED)
    message(STATUS "CUDA Toolkit found. Include dirs: ${CUDAToolkit_INCLUDE_DIRS}")
    file(GLOB CUDA_SOURCES "cuda/*.cu")
    target_include_directories(QuantumFractalEngine PRIVATE ${CUDAToolkit_INCLUDE_DIRS})
    add_compile_definitions(ENABLE_CUDA)
else()
    message(WARNING "CUDA Compiler NOT found. CUDA features will be disabled.")
endif()

# --- Dependencies ---
include(FetchContent)

# GLFW
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG latest)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG master)
FetchContent_MakeAvailable(glm)

# Include Directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# --- Sources ---
# Explicitly list source files for better control
set(SOURCES
    src/main.cpp src/glad.c src/MathEngine.cpp src/PhysicsEngine.cpp src/QuantumEngine.cpp
    src/TerrainEngine.cpp src/Renderer.cpp src/Shader.cpp
)

# --- Executable ---
add_executable(QuantumFractalEngine ${SOURCES} ${CUDA_SOURCES})

# --- Linking ---
target_link_libraries(QuantumFractalEngine PRIVATE glfw glm ${CMAKE_DL_LIBS})

if(WIN32)
    target_link_libraries(QuantumFractalEngine PRIVATE opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(QuantumFractalEngine PRIVATE OpenGL::GL)
endif()

# Add C++17 features
target_compile_features(QuantumFractalEngine PRIVATE cxx_std_17)

if(CMAKE_CUDA_COMPILER)
    target_link_libraries(QuantumFractalEngine PRIVATE CUDA::cudart)
endif()

# --- Copy Shaders to Build Folder ---
add_custom_command(TARGET QuantumFractalEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/shaders
)