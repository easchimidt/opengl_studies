//
// Created by Emanuel Schimidt on 30/09/16.
//

#include <OpenGL/gl3.h>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RotatingSquare.h"
#include "Window.h"
#include "MeshFactory.h"

using namespace std;

void RotatingSquare::init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    angleX = 1.0f;
    angleY = 0.0f;
    firstMouse = true;

//    mesh = MeshFactory::createCube();
//    mesh = MeshFactory::createPlainene(15, 15);
//    mesh = MeshFactory::createSphere(0.5f, 32, 32);
     mesh = MeshFactory::loadTerrain("/Users/emanuel/Documents/Pos/Jogos_3D/img/terrain/river.png", 0.2f);
//    mesh = MeshFactory::createSquare();
    camera = new Camera();
}

void RotatingSquare::update(GLfloat secs) {
    handleKeysPressed(secs);
}

float angle = 0;
void RotatingSquare::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float radius = 1;
    GLfloat camX = sin(glfwGetTime()) * radius;
    GLfloat camZ = cos(glfwGetTime()) * radius;

    //camera->setPosition(glm::vec3(camX, 0.0, camZ));

    mesh->getShader()
      ->bind()
        ->setUniform("uProjection", camera->getProjectionMatrix())
        ->setUniform("uView", camera->getViewMatrix())
        ->setUniform("uAmbientLight", glm::vec3(1.0f, 1.0f, 1.0f))
      ->unbind();

    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::rotate(matrix, angleX, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, angleY, glm::vec3(1.0f, 0.0f, 0.0f));

    mesh->setUniform("uWorld", matrix);
    mesh->draw();
}
void RotatingSquare::deinit() {
}

RotatingSquare::~RotatingSquare() {
    delete(mesh);
    delete(camera);
}

void RotatingSquare::mousePos(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastMouseX;
    GLfloat yoffset = lastMouseY - ypos; // invertido pois Y é negativo abaixo

    lastMouseX = xpos;
    lastMouseY = ypos;

    camera->handleMouseMovement(xoffset, yoffset);
}

void RotatingSquare::mouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
    camera->handleMouseScroll(xoffset, yoffset);
}

void RotatingSquare::keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key > 0 && key < 1024) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void RotatingSquare::handleKeysPressed(GLfloat secs) {
    float step = 5.0f * secs;

//    if (keys[GLFW_KEY_A])
//        angleX -= step;
//    if (keys[GLFW_KEY_D])
//        angleX += step;
//    if (keys[GLFW_KEY_W])
//        angleY -= step;
//    if (keys[GLFW_KEY_S])
//        angleY += step;
    if (keys[GLFW_KEY_W])
        camera->moveFrontBack(1, step);
    if (keys[GLFW_KEY_S])
        camera->moveFrontBack(-1, step);
    if (keys[GLFW_KEY_A])
        camera->strafe(-1, step);
    if (keys[GLFW_KEY_D])
        camera->strafe(1, step);
    if (keys[GLFW_KEY_Z])
        camera->moveUpDown(1, step);
    if (keys[GLFW_KEY_C])
        camera->moveUpDown(-1, step);

}

int main(void) {
    Window *window = new Window(new RotatingSquare(), /*use_mouse*/ true);
    window->show();
}