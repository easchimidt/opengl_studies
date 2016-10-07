//
// Created by Emanuel Schimidt on 30/09/16.
//

#ifndef ESTUDOSOPENGL_SCENE_H
#define ESTUDOSOPENGL_SCENE_H

#include <GLFW/glfw3.h>

class Scene
{
public:
    Scene() {}
    virtual ~Scene() {}
    virtual void init() = 0;
    virtual void update(float secs) = 0;
    virtual void draw() = 0;
    virtual void deinit() = 0;
    virtual void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) = 0;
};

#endif //ESTUDOSOPENGL_SCENE_H
