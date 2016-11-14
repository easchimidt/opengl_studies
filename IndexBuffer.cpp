#include <OpenGL/gl3.h>
#include <stdexcept>

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const std::vector<int>& data) {
    if (data.size() == 0) {
		throw std::invalid_argument("Cannot create Index Buffer. Number of bytes must be bigger then 0." );
    }
    
	totalBytes = data.size() * sizeof(int);
    numElements = data.size();

    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalBytes, &data[0], GL_STATIC_DRAW);
    unbind();
}

void IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::draw() {
    bind();
    glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
    unbind();
}