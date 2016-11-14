//
// Created by Emanuel Schimidt on 17/10/16.
//

#ifndef ESTUDOSOPENGL_MESH_H
#define ESTUDOSOPENGL_MESH_H

#include <map>
#include <string>
#include "Shader.h"
#include "IndexBuffer.h"
#include "UniformType.h"

class Mesh {

    GLuint id;
    Shader *shader;
    IndexBuffer *buffer;
    std::map <std::string, ArrayBuffer*> attributes;

    std::map <std::string, glm::vec2> uniforms2fv;
    std::map <std::string, glm::vec3> uniforms3fv;
    std::map <std::string, glm::vec4> uniforms4fv;
    std::map <std::string, glm::mat4> uniforms4fm;
public:
    Mesh();
    Mesh(GLuint id);
    ~Mesh();

    GLuint getId(){ return id; }
    Shader* setShader(Shader* _shader) { shader = _shader; return shader;}
    Shader* getShader(){ return shader; }
    IndexBuffer* getBuffer(){ return buffer; }
    Mesh* setIndexBuffer(IndexBuffer *indexBuffer) { buffer = indexBuffer; return this;} ;

    void addAttribute(std::string name, ArrayBuffer* data);

    template<typename T>
    Mesh* setUniform(std::string name, T* value);
    Mesh* deleteUniform(std::string name);
    Mesh* setUniform(std::string name, glm::vec2 value);
    Mesh* setUniform(std::string name, glm::vec3 value);
    Mesh* setUniform(std::string name, glm::vec4 value);
    Mesh* setUniform(std::string name, glm::mat4 value);

    Mesh* draw();
};


#endif //ESTUDOSOPENGL_MESH_H
