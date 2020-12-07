#include <glad/glad.h>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Camera.h"
#include "DeltaTime.hpp"
#include "BoxGameObject.hpp"

int main(int /*argc*/, char ** /*argv*/) {
    Camera camera{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f};
    Window window{};
    DeltaTime dt{};
    BoxGameObject box{};

    glm::mat4 projection = glm::perspective(45.0f, window.getAsepct(), 0.1f, 100.0f);

    while (!window.shouldClose()) {
        dt.tick();
        camera.keyControl(window.getKeys(), dt);
        camera.mouseControl(window.getXChange(), window.getYChange());

        window.swapBuffers();

        const glm::mat4 &view = camera.calculateViewMatrix();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        box.render(projection, view);
        glFlush();

        window.pollEvents();
    }
    return 0;
}
