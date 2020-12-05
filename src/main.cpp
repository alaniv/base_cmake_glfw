#include <glad/glad.h>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"

std::vector<Mesh *> meshList;
Shader *ourShader;

void init() {
    GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    GLuint indices[] = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

    Mesh *obj1 = new Mesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    ourShader = new Shader("./media/triangles.vert", "./media/triangles.frag");
    ourShader->use();
}

void display() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    meshList[0]->renderMesh();
    glFlush();
}

int main(int /*argc*/, char ** /*argv*/) {
    Window window{};
    init();

    GLuint uniformProjection = ourShader->uniformProjection;
    GLuint uniformModel = ourShader->uniformModel;
    GLuint uniformView = ourShader->uniformView;

    while (!window.shouldClose()) {
        window.swapBuffers();

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);

        model = glm::translate(model, glm::vec3(0.2f, 0.2f, 0.2f));

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        display();
        window.pollEvents();
    }
    return 0;
}
