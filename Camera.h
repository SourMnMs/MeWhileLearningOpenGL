//
// Created by sourmnms on 2/4/26.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    enum Camera_Movement {FORWARD, BACKWARD, LEFT, RIGHT};
    void updateCameraVectors();

public:
    // camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw = -90.0f;
    float pitch = 0.0f;

    float speed = 2.5f;
    float sensitivity = 0.1f;
    float zoom = 45.0f;

    Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(Camera_Movement dir, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yOffset);
};


#endif //CAMERA_H