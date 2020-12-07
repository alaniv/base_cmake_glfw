#pragma once

#include <vector>
#include <glad/glad.h>

class GLFWwindow;


class Window {
  public:
    Window(GLint windowWidth = WINDOW_WIDTH, GLint windowHeight = WINDOW_HEIGHT);
    ~Window();

    bool shouldClose();
    void swapBuffers();
    void pollEvents();

    const std::vector<int>& getKeys() { return keys; }

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

    // GLfloat getBufferWidth() { return static_cast<GLfloat>(bufferWidth); }
    // GLfloat getBufferHeight() { return static_cast<GLfloat>(bufferHeight); }
    GLfloat getAsepct() { return static_cast<GLfloat>(bufferWidth) / static_cast<GLfloat>(bufferHeight); }

  private:
    static constexpr const char* WINDOW_TITLE = "LearnOpenGL";
    static constexpr GLint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

    GLFWwindow *mainWindow;
    GLint windowWidth, windowHeight;
    int bufferWidth, bufferHeight;

    static constexpr size_t keys_size = 512;
    std::vector<int> keys;

    GLfloat lastX = 0.0f, lastY = 0.0f, xChange = 0.0f, yChange = 0.0f; // mouse
    bool mouseFirstMoved = false;

    friend void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
    friend void handleMouse(GLFWwindow *window, double xPos, double yPos);
};
