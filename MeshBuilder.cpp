//
// Created by Emanuel Schimidt on 02/11/16.
//

#include "MeshBuilder.h"

MeshBuilder::MeshBuilder() {
    mesh = new Mesh();
    glBindVertexArray(mesh->getId());
}

MeshBuilder::~MeshBuilder() {
    delete(mesh);
}

MeshBuilder* MeshBuilder::addBufferAttribute(std::string name, ArrayBuffer* value) {
    mesh->addAttribute(name, value);
    return this;
}

MeshBuilder* MeshBuilder::addFloatArrayAttribute(std::string name, int elementSize, const std::vector<float>& values) {
    addBufferAttribute( name, new ArrayBuffer(elementSize, values));
    return this;
}

MeshBuilder* MeshBuilder::addVector2fAttribute(std::string name, const std::vector<float>& values) {
    return addFloatArrayAttribute(name, 2, values);
}

MeshBuilder* MeshBuilder::addVector2fAttribute(std::string name, int array_size, float* values) {
    std::vector<float> vectorValues(values, values+array_size);
    return addFloatArrayAttribute(name, 2, vectorValues);
}

MeshBuilder* MeshBuilder::addVector3fAttribute(std::string name, const std::vector<float>& values) {
    return addFloatArrayAttribute(name, 3, values);
}

MeshBuilder* MeshBuilder::addVector3fAttribute(std::string name, int array_size, float* values) {
    std::vector<float> vectorValues(values, values+array_size);
    return addFloatArrayAttribute(name, 3, vectorValues);
}

MeshBuilder* MeshBuilder::addVector4fAttribute(std::string name, const std::vector<float>& values) {
    return addFloatArrayAttribute(name, 4, values);
}

MeshBuilder* MeshBuilder::addVector4fAttribute(std::string name, int array_size, float* values) {
    std::vector<float> vectorValues(values, values+array_size);
    return addFloatArrayAttribute(name, 4, vectorValues);
}

MeshBuilder* MeshBuilder::setIndexBuffer(IndexBuffer* indexBuffer) {
    this->mesh->setIndexBuffer(indexBuffer);
    return this;
}

MeshBuilder* MeshBuilder::setIndexBuffer(const std::vector<int>& values) {
    return setIndexBuffer(new IndexBuffer(values));
}

MeshBuilder* MeshBuilder::setIndexBuffer(int array_size, int* values) {
    std::vector<int> indexBuffer(values, values+array_size);
    return setIndexBuffer(indexBuffer);
}

MeshBuilder* MeshBuilder::setShader(Shader* shader) {
    mesh->setShader(shader);
    return this;
}
MeshBuilder* MeshBuilder::loadShader(std::initializer_list<std::string> shaders) {
    mesh->setShader(Shader::loadProgram( { "/Users/emanuel/ClionProjects/estudosOpenGL/shader/shader" }));
    return this;
}

Mesh* MeshBuilder::create() {
    glBindVertexArray(0);
    return this->mesh;
}

