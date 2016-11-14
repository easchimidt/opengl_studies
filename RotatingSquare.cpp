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

using namespace std;

void RotatingSquare::init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    mesh = (new MeshBuilder())
            ->addVector3fAttribute("aPosition",
                  {-0.5f, 0.5f, 0.5f, // 0. top, front, left
                  -0.5f, -0.5f, 0.5f, // 1. bottom, front, left
                  0.5f, -0.5f, 0.5f, // 2. bottom, front, right
                  0.5f, 0.5f, 0.5f, // 3. top, front, right

                  0.5f, 0.5f, -0.5f, // 4. top, back, right
                  0.5f, -0.5f, -0.5f, // 5. bottom, back, right

                  -0.5f, 0.5f, -0.5f, // 6. top, back, left
                  -0.5f, -0.5f, -0.5f // 7. bottom, back, left)
                 })
            ->addVector3fAttribute("aColor",
                 {0.0f, 0.0f, 1.0f,
                  0.0f, 1.0f, 0.0f,
                  1.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f,
                  0.0f, 1.0f, 0.0f,
                  1.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f,
                  0.0f, 1.0f, 0.0f}
            )
            ->setIndexBuffer(
                    {// front
                    0, 1, 2,
                    3, 0, 2,
                    // right
                    3, 2, 5,
                    4, 3, 5,
                    // back
                    4, 5, 6,
                    6, 5, 7,
                    // left
                    6, 7, 0,
                    0, 7, 1,
                    // top
                    6, 0, 3,
                    4, 6, 3,
                    // bottom
                    1, 7, 5,
                    2, 1, 5}
            )
            ->loadShader({ "/Users/emanuel/ClionProjects/estudosOpenGL/shader/shader" })
            ->create();
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