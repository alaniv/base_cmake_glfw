#include "Window.h"

#include <stdexcept>
#include <GLFW/glfw3.h>

namespace {
class AppGlfwError : public std::runtime_error {
  public:
    AppGlfwError(const std::string &message) : std::runtime_error(std::string("ERROR: ") + message) { glfwTerminate(); }
};
} // namespace

void handleKeys(GLFWwindow *window, int key, int code, int action, int mode) {
    Window *mainWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (mainWindow == nullptr)
        throw AppGlfwError(std::string("Window handleKeys: glfwGetWindowUserPointer error."));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            mainWindow->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            mainWindow->keys[key] = false;
        }
    }
}

void handleMouse(GLFWwindow *window, double xPos, double yPos) {
    Window *mainWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (mainWindow == nullptr)
        throw AppGlfwError(std::string("Window handleMouse: glfwGetWindowUserPointer error."));
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

void framebuffer_size_callback(__attribute__((unused)) GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(GLint wwindowWidth, GLint wwindowHeight) : windowWidth{wwindowWidth}, windowHeight{wwindowHeight} {
    keys.fill(false);
    if (!glfwInit())
        throw AppGlfwError(std::string("Window: glfwInit error."));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X
#endif
    mainWindow = glfwCreateWindow(windowWidth, windowHeight, WINDOW_TITLE, nullptr, nullptr);
    if (mainWindow == nullptr)
        throw AppGlfwError(std::string("Window: glfwCreateWindow error."));
    glfwMakeContextCurrent(mainWindow);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hides cursor

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw AppGlfwError(std::string("Window: gladLoadGLLoader error."));

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, bufferWidth, bufferHeight);
    glfwSetWindowUserPointer(mainWindow, this);
}

Window::~Window() { glfwTerminate(); }

bool Window::shouldClose() { return glfwWindowShouldClose(mainWindow); }
void Window::swapBuffers() { glfwSwapBuffers(mainWindow); }
void Window::pollEvents() { glfwPollEvents(); }