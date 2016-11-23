#include <iostream>
#include <vector>

#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLFW/glfw3.h>

using namespace std;

const char* VERTEX_SHADER =
        "#version 330\n"
        "in vec2 aPosition;\n"
        "void main() { \n"
        "    gl_Position = vec4(aPosition, 0.0, 1.0);\n"
        "}";

const char* FRAGMENT_SHADER =
        "#version 330\n"
        "out vec4 out_color;\n"
        "void main() { \n"
        "    out_color = vec4(1.0, 1.0, 0.0, 1.0);\n"
        "}";


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
    GLFWwindow *window;
    GLuint vao;
    GLuint positions;
    int shader;

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(640, 480, "Teste OpenGL", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenVertexArrays(1, &vao);

    float vertexData[] = {
            0.0f, 0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f
    };

    glGenBuffers(1, &positions);

    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertexData, GL_STATIC_DRAW);

    int vertex = compileShader(GL_VERTEX_SHADER, VERTEX_SHADER);
    if (vertex == -1) exit(1);
    int frag = compileShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER);
    if (frag == -1) return 1;

    shader = linkProgram( {vertex, frag });

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);
        GLuint aPosition = glGetAttribLocation(shader, "aPosition");
        glEnableVertexAttribArray(aPosition);
        glBindBuffer(GL_ARRAY_BUFFER, positions);
        glVertexAttribPointer(aPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(aPosition);
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}