//
// Created by Emanuel Schimidt on 30/09/16.
//

#ifndef ESTUDOSOPENGL_SCENE_H
#define ESTUDOSOPENGL_SCENE_H

#include <GLFW/glfw3.h>

class Scene
{
public:
    bool keys[1024];                // keys pressed
    bool firstMouse;                // control first mouse handler loop to avoid a jump in camera position
    GLfloat lastMouseX, lastMouseY; // last mouse positions

    Scene() {}
    virtual ~Scene() {}
    virtual void init() = 0;
    virtual void update(GLfloat secs) = 0;
    virtual void draw() = 0;
    virtual void deinit() = 0;
    virtual void mousePos(GLFWwindow* window, double xpos, double ypos) = 0;
    virtual void mouseScroll(GLFWwindow* window, double xpos, double ypos) = 0;
    virtual void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) = 0;
    virtual void handleKeysPressed(GLfloat secs) = 0;
};

#endif //ESTUDOSOPENGL_SCENE_H
