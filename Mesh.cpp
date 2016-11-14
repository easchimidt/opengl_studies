//
// Created by Emanuel Schimidt on 17/10/16.
//

#include "Mesh.h"

Mesh::Mesh() {
    glGenVertexArrays(1, &id);
}

Mesh::Mesh(GLuint _id) : id(_id) {}

Mesh::~Mesh() {
    for (std::map<std::string, ArrayBuffer *>::iterator it = attributes.begin();
         it != attributes.end(); ++it) {
        delete(it->second);
    }

    /*
    std::map<std::string, glm::vec2>::const_iterator iter2;
    for (iter2 = uniforms2fv.begin(); iter2 != uniforms2fv.end(); ++iter2) {
        delete(iter2->second);
    }

    std::map<std::string, glm::vec3>::const_iterator iter3;
    for (iter3 = uniforms3fv.begin(); iter3 != uniforms3fv.end(); ++iter3) {
        delete(iter3->second);
    }

    std::map<std::string, glm::vec4>::const_iterator iter4;
    for (iter4 = uniforms4fv.begin(); iter4 != uniforms4fv.end(); ++iter4) {
        delete(iter4->second);
    }

    std::map<std::string, glm::mat4>::const_iterator iter4m;
    for (iter4m = uniforms4fm.begin(); iter4m != uniforms4fm.end(); ++iter4m) {
        delete(iter4m->second);
    }
*/
    delete(shader);
    delete(buffer);
}

void Mesh::addAttribute(std::string name, ArrayBuffer* data) {
    attributes[name] = data;
}

template<typename T>
Mesh* Mesh::setUniform(std::string name, T* value) {
    UniformType ut = new UniformType(value);
}

Mesh* Mesh::deleteUniform(std::string name) {
    uniforms2fv.erase(name);
    uniforms3fv.erase(name);
    uniforms4fv.erase(name);
    uniforms4fm.erase(name);
}

Mesh* Mesh::setUniform(std::string name, glm::vec2 value) {
    uniforms2fv[name] = value;
    return this;
}

Mesh* Mesh::setUniform(std::string name, glm::vec3 value) {
    uniforms3fv[name] = value;
    return this;
}

Mesh* Mesh::setUniform(std::string name, glm::vec4 value) {
    uniforms4fv[name] = value;
    return this;
}

Mesh* Mesh::setUniform(std::string name, glm::mat4 value) {
    uniforms4fm[name] = value;
    return this;
}


Mesh* Mesh::draw() {
    if (shader == nullptr || attributes.size() == 0) {
        return this;
    }

    glBindVertexArray(id);

    shader->bind();

    for (std::map<std::string, ArrayBuffer *>::iterator it = attributes.begin();
         it != attributes.end(); ++it) {
        buffer->bind();
        shader->setAttribute(it->first, it->second);
        buffer->unbind();
    }

    std::map<std::string, glm::vec2>::const_iterator iter2;
    for (iter2 = uniforms2fv.begin(); iter2 != uniforms2fv.end(); ++iter2) {
        shader->setUniform(iter2->first, iter2->second);
    }

    std::map<std::string, glm::vec3>::const_iterator iter3;
    for (iter3 = uniforms3fv.begin(); iter3 != uniforms3fv.end(); ++iter3) {
        shader->setUniform(iter3->first, iter3->second);
    }

    std::map<std::string, glm::vec4>::const_iterator iter4;
    for (iter4 = uniforms4fv.begin(); iter4 != uniforms4fv.end(); ++iter4) {
        shader->setUniform(iter4->first, iter4->second);
    }

    std::map<std::string, glm::mat4>::const_iterator iter4m;
    for (iter4m = uniforms4fm.begin(); iter4m != uniforms4fm.end(); ++iter4m) {
        shader->setUniform(iter4m->first, iter4m->second);
    }

    if (buffer == nullptr) {
        attributes.begin()->second->draw();
    } else {
        buffer->draw();
    }

    for (std::map<std::string, ArrayBuffer *>::const_iterator it = attributes.begin();
            it != attributes.end(); ++it) {
        shader->setAttribute(it->first, nullptr);
    }

    shader->unbind();
    glBindVertexArray(0);

    return this;
}