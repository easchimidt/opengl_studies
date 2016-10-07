#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
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

string* readFile(const char* filename) {
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

    // Lines below are needed in Linux
    glewExperimental = GL_TRUE;
    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenVertexArrays(1, &vao);

    float vertexData[] = {
            0.0f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f
    };

    float cubeVertex[] = {
        -0.5f, 0.5f, 0.5f, // 0. top, front, left
        -0.5f, -0.5f, 0.5f, // 1. bottom, front, left
        0.5f, -0.5f, 0.5f, // 2. bottom, front, right
        0.5f, 0.5f, 0.5f, // 3. top, front, right

        0.5f, 0.5f, -0.5f, // 4. top, back, right
        0.5f, -0.5f, -0.5f, // 5. bottom, back, right

        -0.5f, 0.5f, -0.5f, // 6. top, back, left
        -0.5f, -0.5f, -0.5f, // 7. bottom, back, left
    };

    float vertexColor[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f
    };

    int indexData[] = {
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
    // glGenBuffers(1, &colors);
    // glBindBuffer(GL_ARRAY_BUFFER, colors);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
    colors = new ArrayBuffer(sizeof(vertexColor), vertexColor);

    // Position attribution
    // glGenBuffers(1, &positions);
    // glBindBuffer(GL_ARRAY_BUFFER, positions);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertex), cubeVertex, GL_STATIC_DRAW);
    positions = new ArrayBuffer(sizeof(cubeVertex), cubeVertex);

    // Position index attribution
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

    int vertex = compileShader(GL_VERTEX_SHADER, readFile("/home/05367019978/Desenvolvimento/opengl/estudosOpenGL/shader.vert")->c_str());
    int frag = compileShader(GL_FRAGMENT_SHADER, readFile("/home/05367019978/Desenvolvimento/opengl/estudosOpenGL/shader.frag")->c_str());

    shader = linkProgram( {vertex, frag });

    // Clean up mess
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Triangle::update(float secs) {

}

void Triangle::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(vao);

    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::rotate(matrix, angleX, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, angleY, glm::vec3(1.0f, 0.0f, 0.0f));

    // Set uWorld
    int uWorld = glGetUniformLocation(shader, "uWorld");
    glUniformMatrix4fv(uWorld, 1, GL_FALSE, glm::value_ptr(matrix));

    // Set vertex position
    GLuint aPosition = glGetAttribLocation(shader, "aPosition");
    glEnableVertexAttribArray(aPosition);
    // glBindBuffer(GL_ARRAY_BUFFER, positions);
    positions->bind();
    glVertexAttribPointer(aPosition, 3, GL_FLOAT, false, 0, 0);

    // Set vertex color
    GLuint aColor = glGetAttribLocation(shader, "aColor");
    glEnableVertexAttribArray(aColor);
    // glBindBuffer(GL_ARRAY_BUFFER, colors);
    colors->bind();
    glVertexAttribPointer(aColor, 3, GL_FLOAT, false, 0, 0);

    // positions->draw();
    // glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(aPosition);
    glDisableVertexAttribArray(aColor);
    positions->unbind();
    colors->unbind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void printGLCharMessage(vector<GLchar> message) {
    for (vector<char>::const_iterator i = message.begin(); i != message.end(); ++i)
        cout << *i;
}

int compileShader(int shaderType, const char* code) {
    int shader = glCreateShader(shaderType);

    if (shader == 0) {
        cout << "Error creating shader!" << endl;
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
    Window *window = new Window(new Triangle(), 800, 600, "");
    window->show();
}
