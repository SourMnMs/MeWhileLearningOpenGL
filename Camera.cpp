//
// Created by sourmnms on 2/4/26.
//

#include "Camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
{
    position = pos;
    worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
    position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

// returns the view matrix from Euler Angles and the LookAt matrix
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position+front, up);
}


// calculates front vector from updated Euler Angles
void Camera::updateCameraVectors()
{
    // new front vector
    front = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        glm::radians(pitch),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        ));
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}


// alter the ENUM to allow more inputs
void Camera::ProcessKeyboard(Camera_Movement dir, float deltaTime)
{
    float velocity = speed * deltaTime;
    if (dir == FORWARD) position += front*velocity;
    if (dir == BACKWARD) position -= front*velocity;
    if (dir == LEFT) position -= right*velocity;
    if (dir == RIGHT) position += right*velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
    xOffset *= sensitivity;
    yOffset *= sensitivity;
    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
    zoom -= (float) yOffset;
    if (zoom < 1.0f) zoom = 1.0f;
    if (zoom > 45.0f) zoom = 45.0f;
}
