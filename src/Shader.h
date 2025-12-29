// Shader utility: loading and compiling GLSL shaders
#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int ID = 0;
    Shader(const char* vertPath, const char* fragPath);
    Shader(const char* computePath);
    ~Shader();

    void use();
    void setFloat(const std::string &name, float value) const;
    void setInt(const std::string &name, int value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};