#include <glad/glad.h>
#include <vector>

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"

std::vector<Mesh *> meshList;

void init() {
    GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    GLuint indices[] = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

    Mesh *obj1 = new Mesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    Shader ourShader("./media/triangles.vert", "./media/triangles.frag");
    ourShader.use();
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
    while (!window.shouldClose()) {
        display();
        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}
