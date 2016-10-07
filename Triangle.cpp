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


using namespace std;

int compileShader(int shaderType, const char* code);
int linkProgram(initializer_list<int> shaders);


string* readFile(char* filename) {
    ifstream file(filename);
    string *fileContent;

    if (file.is_open()) {
        fileContent = new string((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
    }
    else {
        cout << "Error reading file " << filename << ". Error: " << strerror(errno) << endl;
    }
    file.close();
    return fileContent;
}

void Triangle::init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenVertexArrays(1, &vao);

    float vertexData[] = {
            0.0f, 0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f
    };

    float vertexColor[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f
    };

    int indexData[] = {
            0, 1, 2
    };

    // Color attribution
    glGenBuffers(1, &colors);
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexColor, GL_STATIC_DRAW);

    // Position attribution
    glGenBuffers(1, &positions);
    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertexData, GL_STATIC_DRAW);

    // Position index attribution
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(int), indexData, GL_STATIC_DRAW);
    //(sizeof(indexData)/sizeof(indexData[0]))

    int vertex = compileShader(GL_VERTEX_SHADER, readFile("/Users/emanuel/ClionProjects/estudosOpenGL/shader.vert")->c_str());
    int frag = compileShader(GL_FRAGMENT_SHADER, readFile("/Users/emanuel/ClionProjects/estudosOpenGL/shader.frag")->c_str());

    shader = linkProgram( {vertex, frag });

    // Clean up mess
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Triangle::update(float secs) {

}

float angle = 0;
void Triangle::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(vao);

    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::rotate(matrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));

    // Set uWorld
    int uWorld = glGetUniformLocation(shader, "uWorld");
    glUniformMatrix4fv(uWorld, 1, GL_FALSE, glm::value_ptr(matrix));

    // Set vertex position
    GLuint aPosition = glGetAttribLocation(shader, "aPosition");
    glEnableVertexAttribArray(aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glVertexAttribPointer(aPosition, 2, GL_FLOAT, false, 0, 0);

    // Set vertex color
    GLuint aColor = glGetAttribLocation(shader, "aColor");
    glEnableVertexAttribArray(aColor);
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glVertexAttribPointer(aColor, 3, GL_FLOAT, false, 0, 0);

//    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(aPosition);
    glDisableVertexAttribArray(aColor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}
void Triangle::deinit() {

}
void Triangle::keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void printGLCharMessage(vector<GLchar> message) {
    for (vector<char>::const_iterator i = message.begin(); i != message.end(); ++i)
        cout << *i;
}

int compileShader(int shaderType, const char* code) {
    int shader = glCreateShader(shaderType);

    if (shader == 0) {
        cout << "Erro ao criar o shader!" << endl;
        return -1;
    }
    glShaderSource(shader, 1, &code, NULL);

    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        cout << "Unable to compile shader. " << endl;
        printGLCharMessage(errorLog);

        return -1;
    }

    return shader;
}

int linkProgram(initializer_list<int> shaders) {
    int program = glCreateProgram();

    for( auto shader : shaders) {
        glAttachShader(program, shader);
    }

    glLinkProgram(program);
    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);

        cout << "Unable to link shaders. " << endl;
        printGLCharMessage(errorLog);
        return -1;
    }

    for (auto shader : shaders) {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }
    return program;
}



int main(void) {
    Window *window = new Window(new Triangle());
    window->show();
}