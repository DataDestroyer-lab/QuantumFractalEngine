cmake_minimum_required(VERSION 3.14)
project(QuantumFractalEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Simple portable CMake: builds all .cpp in src/ into QuantumFractalEngine

# Gather sources
file(GLOB_RECURSE PROJECT_SOURCES_CPP CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE PROJECT_SOURCES_C CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.c)
set(PROJECT_SOURCES ${PROJECT_SOURCES_CPP} ${PROJECT_SOURCES_C})

add_executable(QuantumFractalEngine ${PROJECT_SOURCES})

# Include local headers
target_include_directories(QuantumFractalEngine PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# FetchContent for common header-only / small deps (GLFW, GLM)
include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG latest)
FetchContent_MakeAvailable(glfw)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG master)
FetchContent_MakeAvailable(glm)

if(WIN32)
    target_compile_definitions(QuantumFractalEngine PRIVATE _WINDOWS)
    target_link_libraries(QuantumFractalEngine PRIVATE opengl32 glfw glm)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(QuantumFractalEngine PRIVATE OpenGL::GL glfw glm)
endif()

# Post-build: copy shaders folder into build dir
add_custom_command(TARGET QuantumFractalEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
)

message(STATUS "QuantumFractalEngine: configured with sources: ${PROJECT_SOURCES}")