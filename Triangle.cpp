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

#include "Triangle.h"
#include "Window.h"
#include "Shader.h"

using namespace std;

void Triangle::init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenVertexArrays(1, &vao);

    std::vector<float> vertexData = {
            0.0f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f
    };

    std::vector<float> cubeVertex = {
            -0.5f, 0.5f, 0.5f, // 0. top, front, left
            -0.5f, -0.5f, 0.5f, // 1. bottom, front, left
            0.5f, -0.5f, 0.5f, // 2. bottom, front, right
            0.5f, 0.5f, 0.5f, // 3. top, front, right

            0.5f, 0.5f, -0.5f, // 4. top, back, right
            0.5f, -0.5f, -0.5f, // 5. bottom, back, right

            -0.5f, 0.5f, -0.5f, // 6. top, back, left
            -0.5f, -0.5f, -0.5f // 7. bottom, back, left
    };

    std::vector<float> vertexColor = {
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f
    };

    std::vector<int> indexData = {
            // front
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
            2, 1, 5
    };

    // Color attribution
    colors = new ArrayBuffer(3, vertexColor);

    // Position attribution
    positions = new ArrayBuffer(3, cubeVertex);

    // Position index attribution
    index = new IndexBuffer(indexData);

    shader = Shader::loadProgram( { "/Users/emanuel/ClionProjects/estudosOpenGL/shader/shader" });

    // Clean up mess
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Triangle::update(float secs) {

}

float angle = 0;
void Triangle::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->bind();
    glBindVertexArray(vao);

    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::rotate(matrix, angleX, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, angleY, glm::vec3(1.0f, 0.0f, 0.0f));

    // Set uWorld
    int uWorld = glGetUniformLocation(shader->id, "uWorld");
    glUniformMatrix4fv(uWorld, 1, GL_FALSE, glm::value_ptr(matrix));

    // Set vertex position
    shader->setAttribute("aPosition", positions);

    // Set vertex color
    shader->setAttribute("aColor", colors);

    index->draw();

    shader->setAttribute("aPosition", nullptr);
    shader->setAttribute("aColor", nullptr);
    positions->unbind();
    colors->unbind();
    glBindVertexArray(0);
    glUseProgram(0);
}
void Triangle::deinit() {
}

Triangle::~Triangle() {
    if (positions) {
        delete positions;
        delete colors;
    }
}

void Triangle::keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
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
    Window *window = new Window(new Triangle());
    window->show();
}