#pragma once

#include <glad/glad.h>

class Mesh {
  public:
    Mesh(GLfloat *vertices, GLuint *indices, GLsizei numOfVertices, GLsizei numOfIndices);
    ~Mesh();
    void renderMesh();

  private:
    GLuint VAO = 0, VBO = 0, IBO = 0;
    GLsizei indexCount = 0;
};