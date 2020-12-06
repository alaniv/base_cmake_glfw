#include <glad/glad.h>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"

#include <GLFW/glfw3.h>
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Mesh *ourMesh;
Shader *ourShader;

void init() {
    GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    GLuint indices[] = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

    ourMesh = new Mesh(vertices, indices, 12, 12);
    ourShader = new Shader("./media/triangles.vert", "./media/triangles.frag");
    ourShader->use();
}

void display() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ourMesh->renderMesh();
    glFlush();
}

int main(int /*argc*/, char ** /*argv*/) {
    Camera camera{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f};
    Window window{};
    init();

    GLuint uniformProjection = ourShader->uniformProjection;
    GLuint uniformModel = ourShader->uniformModel;
    GLuint uniformView = ourShader->uniformView;

    while (!window.shouldClose()) {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        camera.keyControl(window.getKeys(), deltaTime);
        camera.mouseControl(window.getXChange(), window.getYChange());

        window.swapBuffers();

        glm::mat4 model(1.0f);
        const glm::mat4& view = camera.calculateViewMatrix();
        glm::mat4 projection =
            glm::perspective(45.0f, window.getBufferWidth() / window.getBufferHeight(), 0.1f, 100.0f);

        model = glm::translate(model, glm::vec3(0.2f, 0.2f, 0.2f));

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        display();
        window.pollEvents();
    }
    return 0;
}
