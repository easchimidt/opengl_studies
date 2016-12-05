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
#include "Camera.h"

class RotatingSquare : public Scene {
private:
    Mesh* mesh;
    Camera *camera;
    float angle;

public:
    RotatingSquare() {}
    ~RotatingSquare();
    void init();
    void update(GLfloat secs);
    void draw();
    void deinit();
    void mousePos(GLFWwindow* window, double xpos, double ypos);
    void mouseScroll(GLFWwindow* window, double xpos, double ypos);
    void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);
    void handleKeysPressed(GLfloat secs);

    float angleX, angleY;
};

#endif //ESTUDOSOPENGL_TRIANGLE_H
