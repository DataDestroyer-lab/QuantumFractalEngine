#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertPath, const char* fragPath) {
    std::string vCode, fCode;
    std::ifstream vFile, fFile;
    vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vFile.open(vertPath); fFile.open(fragPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vFile.rdbuf(); fShaderStream << fFile.rdbuf();
        vFile.close(); fFile.close();
        vCode = vShaderStream.str(); fCode = fShaderStream.str();
    } catch(...) { std::cout << "ERROR::SHADER::FILE_NOT_READ" << std::endl; }

    const char* vShaderCode = vCode.c_str();
    const char* fShaderCode = fCode.c_str();
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(vertex); glDeleteShader(fragment);
}

Shader::Shader(const char* computePath) {
    std::string code; std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(computePath); std::stringstream ss; ss << file.rdbuf(); file.close(); code = ss.str();
    } catch(...) { std::cout << "ERROR::SHADER::COMPUTE::FILE_NOT_READ: " << computePath << std::endl; }
    
    const char* cCode = code.c_str();
    unsigned int compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &cCode, NULL);
    glCompileShader(compute);
    checkCompileErrors(compute, "COMPUTE");

    ID = glCreateProgram();
    glAttachShader(ID, compute);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(compute);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::use() { glUseProgram(ID); }
void Shader::setFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setInt(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success; char infoLog[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) { glGetShaderInfoLog(shader, 1024, NULL, infoLog); std::cout << "ERR::SHADER::" << type << "\n" << infoLog << std::endl; }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) { glGetProgramInfoLog(shader, 1024, NULL, infoLog); std::cout << "ERR::PROGRAM::LINKING\n" << infoLog << std::endl; }
    }
}