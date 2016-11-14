#ifndef ESTUDOSOPENGL_SHADER_H
#define ESTUDOSOPENGL_SHADER_H

#include <OpenGL/gl3.h>
#include <vector>
#include <glm/glm.hpp>
#include "ArrayBuffer.h"

class Shader {

public:
    Shader(GLuint _id) : id(_id) {}
    ~Shader() {}
    static std::string* readFile(std::string filename);
    static GLuint linkProgram(std::vector<int> shaders);
    static GLuint compileShader(GLuint shaderType, const char* code);
    static std::string getGLCharMessage(std::vector<GLchar> message);
    static Shader* loadProgram(std::initializer_list<std::string> shaders);
    static int loadShader(std::string shader_filename);
    Shader* setAttribute(std::string name, ArrayBuffer* buffer);
    static std::string trim(std::string& str);
    Shader* bind();
    Shader* unbind();

    GLuint findUniform(std::string name);
    Shader* setUniform(std::string name, GLint value);
    Shader* setUniform(std::string name, GLfloat value);
    Shader* setUniform(std::string name, glm::vec2 value);
    Shader* setUniform(std::string name, glm::vec3 vector);
    Shader* setUniform(std::string name, glm::vec4 vector);
    Shader* setUniform(std::string name, glm::mat3 matrix);
    Shader* setUniform(std::string name, glm::mat4 matrix);

    GLuint id;
};

#endif //ESTUDOSOPENGL_SHADER_H
