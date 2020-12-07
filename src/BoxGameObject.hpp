#pragma once

#include <glad/glad.h>

#include "Shader.h"
#include "Mesh.h"
#include <memory>
#include <glm/gtc/type_ptr.hpp>

GLfloat vertices[]{
    -1.0f, -1.0f, -1.0f, //
    1.0f,  -1.0f, -1.0f, //
    -1.0f, 1.0f,  -1.0f, //
    1.0f,  1.0f,  -1.0f, //
    -1.0f, -1.0f, 1.0f,  //
    1.0f,  -1.0f, 1.0f,  //
    -1.0f, 1.0f,  1.0f,  //
    1.0f,  1.0f,  1.0f,  //
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

  public:
    BoxGameObject() {
        ourMesh = std::make_unique<Mesh>(vertices, indices, 24, 36);
        ourShader = std::make_unique<Shader>("./media/triangles.vert", "./media/triangles.frag");
    }
    void render(const glm::mat4 &projection, const glm::mat4 &view) {

        ourShader->use();

        GLuint uniformProjection = ourShader->uniformProjection;
        GLuint uniformModel = ourShader->uniformModel;
        GLuint uniformView = ourShader->uniformView;

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.2f, 0.2f, 0.2f));

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        ourMesh->renderMesh();
    }
};