#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
               GLfloat startMovementSpeed, GLfloat startTurnSpeed, Window &window)
    : mWindow{window}, position{startPosition}, worldUp{startUp}, yaw{startYaw}, pitch{startPitch},
      movementSpeed{startMovementSpeed}, turnSpeed{startTurnSpeed} {
    recalculateAxis();
}

void Camera::recalculateAxis() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::update(GLfloat dt) {
    keyControl(mWindow.getKeys(), dt);
    mouseControl(mWindow.getXChange(), mWindow.getYChange());
}

void Camera::keyControl(const std::vector<int> &keys, GLfloat dt) {
    GLfloat vel = dt * movementSpeed;
    if (keys[GLFW_KEY_W])
        position += front * vel;
    if (keys[GLFW_KEY_S])
        position -= front * vel;
    if (keys[GLFW_KEY_A])
        position -= right * vel;
    if (keys[GLFW_KEY_D])
        position += right * vel;
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    pitch = glm::clamp(pitch, -45.0f, 45.0f);
    recalculateAxis();
}

glm::mat4 Camera::calculateViewMatrix() { return glm::lookAt(position, position + front, up); }
glm::mat4 Camera::calculateProjectionMatrix() { return glm::perspective(45.0f, mWindow.getAsepct(), 0.1f, 100.0f); }
