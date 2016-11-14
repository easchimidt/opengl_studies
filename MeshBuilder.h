//
// Created by Emanuel Schimidt on 02/11/16.
//

#ifndef ESTUDOSOPENGL_MESHBUILDER_H
#define ESTUDOSOPENGL_MESHBUILDER_H


#include <string>
#include <vector>
#include "Mesh.h"

class MeshBuilder {
private:
    Mesh* mesh;

public:
    MeshBuilder();
    ~MeshBuilder();
    MeshBuilder* addBufferAttribute(std::string name, ArrayBuffer* value);
    MeshBuilder* addFloatArrayAttribute(std::string name, int elementSize, const std::vector<float>& values);

    MeshBuilder* addVector2fAttribute(std::string name, const std::vector<float>& values);
    MeshBuilder* addVector2fAttribute(std::string name, int array_size, float* values);

    MeshBuilder* addVector3fAttribute(std::string name, const std::vector<float>& values);
    MeshBuilder* addVector3fAttribute(std::string name, int array_size, float* values);

    MeshBuilder* addVector4fAttribute(std::string name, const std::vector<float>& values);
    MeshBuilder* addVector4fAttribute(std::string name, int array_size, float* values);

    MeshBuilder* setIndexBuffer(IndexBuffer* data);
    MeshBuilder* setIndexBuffer(const std::vector<int>& values);
    MeshBuilder* setIndexBuffer(int array_size, int* values);

    MeshBuilder* setShader(Shader* shader);
    MeshBuilder* loadShader(std::initializer_list<std::string> shaders);

    Mesh* create();
};


#endif //ESTUDOSOPENGL_MESHBUILDER_H
