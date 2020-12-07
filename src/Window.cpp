#include "Window.h"

#include <stdexcept>
#include <GLFW/glfw3.h>

class WindowError : public std::runtime_error {
  public:
    WindowError(const std::string &message) : std::runtime_error(std::string("ERROR::WINDOW:: ") + message) {}
};

void handleKeys(GLFWwindow *window, int key, int code, int action, int mode) {
    Window *mainWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (mainWindow == nullptr)
        throw WindowError(std::string("handleKeys: glfwGetWindowUserPointer error."));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key >= 0 && key < mainWindow->keys_size)
        mainWindow->keys[key] = action;
}

void handleMouse(GLFWwindow *window, double xPos, double yPos) {
    Window *mainWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (mainWindow == nullptr)
        throw WindowError(std::string("handleMouse: glfwGetWindowUserPointer error."));
    if (!mainWindow->mouseFirstMoved) {
        mainWindow->lastX = xPos;
        mainWindow->lastY = yPos;
        mainWindow->mouseFirstMoved = true;
    }
    mainWindow->xChange = xPos - mainWindow->lastX;
    mainWindow->yChange = -yPos + mainWindow->lastY;
    mainWindow->lastX = xPos;
    mainWindow->lastY = yPos;
}

void framebuffer_size_callback(GLFWwindow * /* window */, int width, int height) { glViewport(0, 0, width, height); }

Window::Window(GLint wwindowWidth, GLint wwindowHeight)
    : windowWidth{wwindowWidth}, windowHeight{wwindowHeight}, keys{std::vector<int>(keys_size, GLFW_RELEASE)} {
    if (!glfwInit())
        throw WindowError(std::string("glfwInit error."));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(windowWidth, windowHeight, WINDOW_TITLE, nullptr, nullptr);
    if (mainWindow == nullptr)
        throw WindowError(std::string("glfwCreateWindow error."));
    glfwMakeContextCurrent(mainWindow);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hides cursor

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw WindowError(std::string("gladLoadGLLoader error."));

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, bufferWidth, bufferHeight);
    glfwSetWindowUserPointer(mainWindow, this);
}

Window::~Window() { glfwTerminate(); }

bool Window::shouldClose() { return glfwWindowShouldClose(mainWindow); }
void Window::swapBuffers() { glfwSwapBuffers(mainWindow); }
void Window::pollEvents() { glfwPollEvents(); }