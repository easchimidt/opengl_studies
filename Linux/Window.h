//
// Created by Emanuel Schimidt on 30/09/16.
//

#ifndef ESTUDOSOPENGL_WINDOW_H
#define ESTUDOSOPENGL_WINDOW_H

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

#include "Scene.h"

class Window {
public:
    Window(Scene *_scene, int _width, int _height, std::string _title);
    Window(Scene *_scene, std::string _title);
    Window(Scene *_scene);
    ~Window();
    void init();
    void show();
    void loop();
    static void KeyPressedHandler(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
    Scene *scene;
    GLFWwindow *window;
    int height;
    int width;
    std::string title;
};
#endif //ESTUDOSOPENGL_WINDOW_H
