#include "Texture.h"
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class TextureError : public std::runtime_error {
  public:
    TextureError(const std::string &message) : std::runtime_error("ERROR::TEXTURE:: " + message) {}
};

Texture::Texture(std::string fileLoc) : fileLocation{fileLoc} {}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
    textureId = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = "";
}

void Texture::loadTexture() {
    unsigned char *texData = stbi_load(fileLocation.c_str(), &width, &height, &bitDepth, 0);
    if (texData == nullptr)
        throw TextureError("stbi_load error. file: " + fileLocation);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texData);
}

void Texture::useTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}
