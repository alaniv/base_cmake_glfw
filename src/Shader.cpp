#include "Shader.h"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderError : public std::runtime_error {
  public:
    ShaderError(const std::string &message) : std::runtime_error(std::string("ERROR::SHADER:: ") + message) {}
};

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode = readShaderFile(vertexPath);
    std::string fragmentCode = readShaderFile(fragmentPath);

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERT");

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAG");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkLinkErrors(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() { glUseProgram(ID); }

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

std::string Shader::readShaderFile(const char *path) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path);
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    } catch (const std::exception &e) {
        throw ShaderError("file read error: " + std::string(path));
    }
    std::string ret = shaderStream.str();
    if (ret.empty())
        throw ShaderError("empty file code: " + std::string(path));
    return ret;
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024] = {0};
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        throw ShaderError("GL compiling error: " + type + "\n" + std::string(infoLog));
    }
}

void Shader::checkLinkErrors(GLuint shader) {
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024] = {0};
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        throw ShaderError("GL program linking error: \n" + std::string(infoLog));
    }
}