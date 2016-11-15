//
// Created by Emanuel Schimidt on 30/09/16.
//

#include <OpenGL/gl3.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RotatingSquare.h"
#include "Window.h"
#include "Shader.h"
#include "MeshBuilder.h"
#include "UniformType.h"
#include "MeshFactory.h"

using namespace std;

void RotatingSquare::init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

//    mesh = MeshFactory::createCube();
    mesh = MeshFactory::createPlane(10, 5);
}

void RotatingSquare::update(float secs) {

}

float angle = 0;
void RotatingSquare::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
}

void RotatingSquare::keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_A)
        angleX -= 0.1;
    if (key == GLFW_KEY_D)
        angleX += 0.1;
    if (key == GLFW_KEY_W)
        angleY -= 0.1;
    if (key == GLFW_KEY_S)
        angleY += 0.1;
}

int main(void) {
    Window *window = new Window(new RotatingSquare());
    window->show();
}