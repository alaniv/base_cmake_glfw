#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
  public:
    Texture(std::string fileLoc);
    ~Texture();

    void loadTexture();
    void useTexture();

  private:
    GLuint textureId = 0;
    int width = 0, height = 0, bitDepth = 0;
    std::string fileLocation;
};