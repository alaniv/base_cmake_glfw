#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Window.h"
#include "shader.h"

#define BUFFER_OFFSET(a) ((void *)(a))

void processInput(GLFWwindow *window);

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init() {
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    GLfloat vertices[NumVertices][2] = {{-0.90, -0.90}, {0.85, -0.90}, {-0.90, 0.85},
                                        {0.90, -0.85},  {0.90, 0.90},  {-0.85, 0.90}};
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader ourShader("./media/triangles.vert", "./media/triangles.frag");
    ourShader.use();

    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    glFlush();
}

int main(int /*argc*/, char ** /*argv*/) {
    Window window{};
    init();
    while (!window.shouldClose()) {
        display();
        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}
