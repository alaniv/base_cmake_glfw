#pragma once

#include <GLFW/glfw3.h>

class DeltaTime {
    GLfloat deltaTime = 0.0f;
    GLfloat lastTime = 0.0f;

  public:
    operator GLfloat() { return deltaTime; }
    void tick() {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;
    }
};