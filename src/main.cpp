#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Camera.h"
#include "DeltaTime.hpp"
#include "BoxGameObject.hpp"

void render(BoxGameObject& box, const glm::mat4& projection, const glm::mat4& view) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    box.render(projection, view);
    glFlush();
}

int main(int /*argc*/, char ** /*argv*/) {
    Window window{};
    Camera camera{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f, window};
    DeltaTime dt{};
    BoxGameObject box{};

    glm::mat4 projection{camera.calculateProjectionMatrix()};

    while (!window.shouldClose()) {
        dt.tick();
        camera.update(dt);
        window.swapBuffers();
        glm::mat4 view{camera.calculateViewMatrix()};
        render(box, projection, view);
        window.pollEvents();
    }
    return 0;
}
