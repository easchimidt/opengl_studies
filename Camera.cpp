//
// Created by Emanuel Schimidt on 21/11/16.
//

#include "Camera.h"
#include <GLFW/glfw3.h>

float Camera::getAspect() {
    int w, h;
    GLFWwindow *window = glfwGetCurrentContext();
    glfwGetWindowSize(window, &w, &h);
    return w / (float)h;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(fov, getAspect(), near, far);
}