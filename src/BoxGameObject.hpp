#pragma once

#include <glad/glad.h>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include <memory>
#include <glm/gtc/type_ptr.hpp>

GLfloat vertices[]{
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //
    1.0f,  -1.0f, -1.0f, 1.0f, 0.0f, //
    -1.0f, 1.0f,  -1.0f, 0.0f, 1.0f, //
    1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, //
    -1.0f, -1.0f, 1.0f,  1.0f, 0.0f, //
    1.0f,  -1.0f, 1.0f,  1.0f, 1.0f, //
    -1.0f, 1.0f,  1.0f,  0.0f, 1.0f, //
    1.0f,  1.0f,  1.0f,  1.0f, 0.0f, //
};
GLuint indices[]{
    0, 1, 2, 1, 2, 3, //
    0, 2, 4, 2, 4, 6, //
    1, 3, 5, 3, 5, 7, //
    0, 1, 4, 1, 4, 5, //
    2, 3, 6, 3, 6, 7, //
    4, 5, 6, 5, 6, 7  //
};

class BoxGameObject {
    std::unique_ptr<Mesh> ourMesh;
    std::unique_ptr<Shader> ourShader;
    std::unique_ptr<Texture> ourTexture;
    glm::vec3 position;

  public:
    BoxGameObject() : position{glm::vec3(0.2f, 0.2f, 0.2f)} {
        ourMesh = std::make_unique<Mesh>(vertices, indices, 40, 36);
        ourShader = std::make_unique<Shader>("./media/triangles.vert", "./media/triangles.frag");
        ourTexture = std::make_unique<Texture>("./media/brick.png");
        ourTexture->loadTexture();
    }
    void render(const glm::mat4 &projection, const glm::mat4 &view) {

        ourShader->use();
        ourTexture->useTexture();
        GLuint uniformProjection = ourShader->uniformProjection;
        GLuint uniformModel = ourShader->uniformModel;
        GLuint uniformView = ourShader->uniformView;

        glm::mat4 model{glm::translate(glm::mat4(1.0f), position)};

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        ourMesh->renderMesh();
    }
};