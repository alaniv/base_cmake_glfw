#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera() {}

glm::vec3 Camera::getCameraPosition(){
    return position;
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
               GLfloat startMovementSpeed, GLfloat startTurnSpeed) {
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    movementSpeed = startMovementSpeed;
    turnSpeed = startTurnSpeed;
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

void Camera::keyControl(const bool *keys, GLfloat deltaTime) {
    GLfloat vel = deltaTime * movementSpeed;
    if (keys[GLFW_KEY_W]) {
        position += front * vel;
    }
    if (keys[GLFW_KEY_S]) {
        position -= front * vel;
    }
    if (keys[GLFW_KEY_A]) {
        position -= right * vel;
    }
    if (keys[GLFW_KEY_D]) {
        position += right * vel;
    }
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    glm::clamp(pitch, -89.0f, 89.0f);
    update();
}

glm::mat4 Camera::calculateViewMatrix() { return glm::lookAt(position, position + front, up); }
