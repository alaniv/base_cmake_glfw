#pragma once

#include <glad/glad.h>
#include <string>

class Shader {

  public:
    GLuint ID;
    Shader(const char *vertexPath, const char *fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

  private:
    std::string readShaderFile(const char *path);
    void checkCompileErrors(GLuint shader, std::string type);
    void checkLinkErrors(GLuint shader);
};
