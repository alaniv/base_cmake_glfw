#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Camera {
  public:
    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed,
           GLfloat startTurnSpeed);
    ~Camera();
    void keyControl(const std::vector<int> &keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);
    glm::mat4 calculateViewMatrix();
    glm::vec3 getCameraPosition();

  private:
    glm::vec3 front, right, up, position, worldUp;
    GLfloat yaw, pitch; // no roll
    GLfloat movementSpeed, turnSpeed;

    void update();
};