//
// Created by Emanuel Schimidt on 15/10/16.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

std::string* Shader::readFile(std::string filename) {
    std::ifstream file(filename);
    std::string *fileContent;

    if (file.is_open()) {
        fileContent = new std::string((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());
    }
    else {
        std::ostringstream os;
        os << "Error reading file " << filename << ". Error: " << strerror(errno) << std::endl;
        throw std::invalid_argument(os.str());
    }
    file.close();
    return fileContent;
}

GLuint Shader::linkProgram(std::vector<int> shaders) {
    GLuint program = glCreateProgram();

    for( auto shader : shaders) {
        glAttachShader(program, shader);
    }

    glLinkProgram(program);
    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);

        std::ostringstream os;
        os << "Unable to link shaders. " << getGLCharMessage(errorLog);
        throw std::invalid_argument(os.str());
    }

    for (auto shader : shaders) {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }
    return program;
}

GLuint Shader::compileShader(GLuint shaderType, const char* code) {
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0) {
        throw std::invalid_argument("Error creating shader!");
    }
    glShaderSource(shader, 1, &code, NULL);

    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        std::ostringstream os;
        os << "Unable to compile shaders. " << getGLCharMessage(errorLog);
        throw std::invalid_argument(os.str());
    }

    return shader;
}

std::string Shader::getGLCharMessage(std::vector<GLchar> message) {
    std::ostringstream os;
    for (std::vector<char>::const_iterator i = message.begin(); i != message.end(); ++i) {
        os << *i;
    }
    return os.str();
}

Shader* Shader::bind() {
    glUseProgram(this->id);
    return this;
}

Shader* Shader::unbind() {
    glUseProgram(0);
    return this;
}

/**
 * Call the functions from shader load from disk to link
 * @param shaders Filename of shaders. If vertex and fragment shaders
 * have the same name, user can send only the file name, and the function
 * will append the .vert and .frag extensions.
 * @return The Shader object containing the information of shader files loaded
 */
Shader* Shader::loadProgram(std::initializer_list<std::string> shaders) {
    std::vector<std::string> shader_names;
    if (shaders.size() == 0) {
        throw std::invalid_argument("No shaders received!");
    }

    // Copy parameteres to array
    shader_names.insert(shader_names.end(), shaders);

    if (shader_names.size() == 1) {
        shader_names.insert(shader_names.end(), shader_names[0]);
        shader_names[0].append(".vert");
        shader_names[1].append(".frag");
    }

    std::vector<int> ids;
    for (int i = 0; i < shader_names.size(); i++) {
        ids.push_back(Shader::loadShader(shader_names[i]));
    }

    return new Shader(linkProgram(ids));
}

int Shader::loadShader(std::string shader_filename) {
    shader_filename = Shader::trim(shader_filename);

    std::size_t dot_index = shader_filename.find_last_of(".");
    std::string extension = (dot_index == std::string::npos) ? "" : shader_filename.substr(dot_index+1);

    // convert extension to lower case to avoid problems
    for (std::string::size_type i = 0; i < extension.length(); ++i) {
        extension[i] = std::tolower(extension[i]);
    }

    GLuint type;

    if (extension.compare("vert") == 0 || extension.compare("vs") == 0) {
        type = GL_VERTEX_SHADER;
    }
    else if (extension.compare("frag") || extension.compare("fs")) {
        type = GL_FRAGMENT_SHADER;
    }
    else if (extension.compare("geom") || extension.compare("gs")) {
        type = GL_GEOMETRY_SHADER;
    }
    else {
        std::ostringstream os;
        os << "Invalid shader name: " << shader_filename;
        throw std::invalid_argument(os.str());
    }

    std::string* code = Shader::readFile(shader_filename);
    return Shader::compileShader(type, code->c_str());
}

/**
 * Original trim function from http://yossefmaestro.com/c-plus-plus-trim-function/
 * @param str
 * @return
 */
std::string Shader::trim(std::string& str) {
    // if the first character of the string is a whitespace or a tab
    while (str[0] == ' ' || str[0] == '\t') {
        str.erase(str.begin()); // erase it
    }

    // if the last character of the string is a whitespace or a tab
    while (str[str.length() - 1] == ' ' || str[str.length() - 1] == '\t') {
        str.erase(str.end() - 1); // erase it
    }

    return str;
}

Shader* Shader::setAttribute(std::string name, ArrayBuffer* buffer) {
    GLuint attribute = glGetAttribLocation(id, name.c_str());
    if (attribute == -1) {
        std::ostringstream os;
        os << "Invalid attribute " << name;
        throw std::invalid_argument(os.str());
    }

    if (buffer == nullptr) {
        glDisableVertexAttribArray(attribute);
    }
    else {
        glEnableVertexAttribArray(attribute);
        buffer->bind();
        glVertexAttribPointer(attribute, buffer->element_size, GL_FLOAT, false, 0, 0);
    }
    return this;
}

GLuint Shader::findUniform(std::string name) {
    int uniform = glGetUniformLocation(id, name.c_str());
    if (uniform == -1) {
        std::cout << "Uniform does not exists: " << name << std::endl;
    }
    return uniform;
}

Shader* Shader::setUniform(std::string name, GLint value) {
    GLint uniform = this->findUniform(name);
    if (uniform == -1) return this;

    glUniform1i(uniform, value);

    return this;
}
Shader* Shader::setUniform(std::string name, float value) {
    GLint uniform = this->findUniform(name);
    if (uniform == -1) return this;

    glUniform1f(uniform, value);

    return this;
}

Shader* Shader::setUniform(std::string name, glm::vec2 vector) {
    GLuint uniform = this->findUniform(name);
    if (uniform == -1) return this;

    glUniform2fv(uniform, 1, glm::value_ptr(vector));

    return this;
}

Shader* Shader::setUniform(std::string name, glm::vec3 vector) {
    GLuint uniform = this->findUniform(name);
    if (uniform == -1) return this;

    glUniform3fv(uniform, 1, glm::value_ptr(vector));

    return this;
}

Shader* Shader::setUniform(std::string name, glm::vec4 vector) {
    GLuint uniform = this->findUniform(name);
    if (uniform == -1) return this;

    glUniform4fv(uniform, 1, glm::value_ptr(vector));

    return this;
}

Shader* Shader::setUniform(std::string name, glm::mat3 matrix) {
    GLuint uniform = this->findUniform(name);
    if (uniform == -1) return this;

    glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));

    return this;
}

Shader* Shader::setUniform(std::string name, glm::mat4 matrix) {
    GLuint uniform = this->findUniform(name);
    if (uniform == -1) return this;

    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));

    return this;
}