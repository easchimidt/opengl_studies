//
// Created by Emanuel Schimidt on 21/11/16.
//

#ifndef ESTUDOSOPENGL_CAMERA_H
#define ESTUDOSOPENGL_CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"
#include <iostream>

class Camera {
private:
    GLfloat MAX_ZOOM = 44.0f;
    GLfloat NORMAL_ZOOM = 45.0f;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f); //eye
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); //top
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 1.0f); //center
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    GLfloat fov = 45.0f;
    GLfloat near = 0.01f;
    GLfloat far = 1000.0f;
    GLfloat pitch, yaw, roll;       // euler angles towards each axis
    GLfloat sensitivity = 0.25f;

    float getAspect() {
        int w, h;
        GLFWwindow *window = glfwGetCurrentContext();
        glfwGetWindowSize(window, &w, &h);
        return w / (float)h;
    }

public:
    Camera() {}
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f); // front of the camera
    glm::vec3 getPosition() { return position; }
    glm::vec3 getUp() { return up; }
    glm::vec3 getTarget() { return target; }
    void setFov(float _fov) { fov = _fov; }
    float getFov() { return fov; }
    void setNear(float _near) { near = _near; }
    float getNear() { return near; }
    void setFar(float _far) { far = _far; }
    float getFar() { return far; }

    // lateral movement
    void strafe(int direction, float step) {
        position += right * (direction * step);
    }

    // direction: -1 (front), 1 (back)
    void moveFrontBack(int direction, float step) {
        position += front * (direction * step);
    }

    // direction: -1 (front), 1 (back)
    void moveUpDown(int direction, float step) {
        position += up * (direction * step);
    }

    void rotate(float angle) {
        position.z += angle;
    }

    void handleMouseMovement(GLfloat xoffset, GLfloat yoffset) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 camera_front;
        GLfloat pitch_radians = glm::radians(pitch);
        GLfloat yaw_radians = glm::radians(yaw);

        camera_front.x = cos(pitch_radians) * cos(yaw_radians);
        camera_front.y = sin(pitch_radians);
        camera_front.z = cos(pitch_radians) * sin(yaw_radians);
        front = glm::normalize(camera_front);
    }

    void handleMouseScroll(GLfloat xoffset, GLfloat yoffset) {
        if (fov >= MAX_ZOOM && fov <= NORMAL_ZOOM) {
            fov -= yoffset * sensitivity;
        }
        if (fov <= MAX_ZOOM) fov = MAX_ZOOM;
        if (fov >= NORMAL_ZOOM) fov = NORMAL_ZOOM;
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position+front, up);
    }
    glm::mat4 getProjectionMatrix() {
        return glm::perspective(fov, getAspect(), near, far);
    }
};


#endif //ESTUDOSOPENGL_CAMERA_H
