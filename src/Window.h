#pragma once

#include <array>
#include <glad/glad.h>

class GLFWwindow;

constexpr GLint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
constexpr char WINDOW_TITLE[] = "LearnOpenGL";

class Window {
  public:
    Window(GLint windowWidth = WINDOW_WIDTH, GLint windowHeight = WINDOW_HEIGHT);
    ~Window();

    bool shouldClose();
    void swapBuffers();
    void pollEvents();

    const bool *getKeys() { return keys.data(); }

    GLfloat getXChange() {
        GLfloat theChange = xChange;
        xChange = 0.0f;
        return theChange;
    }
    
    GLfloat getYChange() {
        GLfloat theChange = yChange;
        yChange = 0.0f;
        return theChange;
    }

  private:
    GLFWwindow *mainWindow;
    GLint windowWidth, windowHeight;
    int bufferWidth, bufferHeight;

    std::array<bool, 1024> keys;

    GLfloat lastX = 0.0f, lastY = 0.0f, xChange = 0.0f, yChange = 0.0f; // mouse
    bool mouseFirstMoved = false;

    friend void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
    friend void handleMouse(GLFWwindow *window, double xPos, double yPos);
};
