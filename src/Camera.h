#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Window.h"
class Camera {
  public:
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed,
           GLfloat startTurnSpeed, Window &window);

    glm::mat4 calculateViewMatrix();
    glm::mat4 calculateProjectionMatrix();
    void update(GLfloat deltaTime);

  private:
    Window &mWindow;
    void keyControl(const std::vector<int> &keys, GLfloat dt);
    void mouseControl(GLfloat xChange, GLfloat yChange);
    glm::vec3 front, right, up, position, worldUp;
    GLfloat yaw, pitch; // no roll
    GLfloat movementSpeed, turnSpeed;

    void recalculateAxis();
};