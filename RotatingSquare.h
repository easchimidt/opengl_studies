//
// Created by Emanuel Schimidt on 30/09/16.
//

#ifndef ESTUDOSOPENGL_TRIANGLE_H
#define ESTUDOSOPENGL_TRIANGLE_H

#include "ArrayBuffer.h"
#include "IndexBuffer.h"
#include "Scene.h"
#include "Shader.h"
#include "Mesh.h"

class RotatingSquare : public Scene {
private:
    Mesh* mesh;
    float angle;

public:
    RotatingSquare() {}
    ~RotatingSquare();
    void init();
    void update(float secs);
    void draw();
    void deinit();
    void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

    float angleX, angleY;
};

#endif //ESTUDOSOPENGL_TRIANGLE_H
