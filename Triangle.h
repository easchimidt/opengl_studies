//
// Created by Emanuel Schimidt on 30/09/16.
//

#ifndef ESTUDOSOPENGL_TRIANGLE_H
#define ESTUDOSOPENGL_TRIANGLE_H

#include "Scene.h"

class Triangle : public Scene {
public:
    Triangle() {}
    ~Triangle() {}
    void init();
    void update(float secs);
    void draw();
    void deinit();
    void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

    GLuint vao;
    GLuint positions;
    GLuint colors;
    GLuint index;
    GLuint shader;
};

#endif //ESTUDOSOPENGL_TRIANGLE_H
