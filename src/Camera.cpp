#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
               GLfloat startMovementSpeed, GLfloat startTurnSpeed)
    : position{startPosition}, worldUp{startUp}, yaw{startYaw}, pitch{startPitch},
      movementSpeed{startMovementSpeed}, turnSpeed{startTurnSpeed}
{
    update();
}

Camera::~Camera() {}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::keyControl(const std::vector<int> &keys, GLfloat deltaTime) {
    GLfloat vel = deltaTime * movementSpeed;
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
    update();
}

glm::mat4 Camera::calculateViewMatrix() { return glm::lookAt(position, position + front, up); }

glm::vec3 Camera::getCameraPosition() { return position; }
