//
// Created by Emanuel Schimidt on 30/09/16.
//

#ifndef ESTUDOSOPENGL_TRIANGLE_H
#define ESTUDOSOPENGL_TRIANGLE_H

#include "ArrayBuffer.h"
#include "IndexBuffer.h"
#include "Scene.h"
#include "Shader.h"

class Triangle : public Scene {
public:
    Triangle() {}
    ~Triangle();
    void init();
    void update(float secs);
    void draw();
    void deinit();
    void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

    GLuint vao;
    ArrayBuffer *positions;
    ArrayBuffer *colors;
    IndexBuffer *index;
    Shader* shader;
    float angleX, angleY;
};

#endif //ESTUDOSOPENGL_TRIANGLE_H
