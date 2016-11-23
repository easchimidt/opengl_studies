//
// Created by Emanuel Schimidt on 21/11/16.
//

#ifndef ESTUDOSOPENGL_CAMERA_H
#define ESTUDOSOPENGL_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"

class Camera {
private:
    glm::vec3 position = glm::vec3(10.0f, 100.0f, -30.0f); //eye
    glm::vec3 up = glm::vec3(0, 1, 0); //top
    glm::vec3 target = glm::vec3(0, 0, 0); //center
    float fov = Utils::toRadians(60);
    float near = 0.1f;
    float far = 1000.0f;
    float getAspect();

public:
    Camera() {}
    glm::vec3 getPosition() { return position; }
    glm::vec3 getUp() { return up; }
    glm::vec3 getTarget() { return target; }
    void setFov(float _fov) { fov = _fov; }
    float getFov() { return fov; }
    void setNear(float _near) { near = _near; }
    float getNear() { return near; }
    void setFar(float _far) { far = _far; }
    float getFar() { return far; }

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};


#endif //ESTUDOSOPENGL_CAMERA_H
