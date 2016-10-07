#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdexcept>

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(int _totalBytes, int *data) {
    if (_totalBytes < 1) {
        throw std::invalid_argument("Cannot create Index Buffer. Number of bytes must be bigger then 0." );
    }
    if (data == NULL) {
        throw std::invalid_argument("Cannot create Index Buffer. Data cannot be null.");
    }

    totalBytes = _totalBytes;
    numElements = totalBytes / sizeof(int);

    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalBytes, data, GL_STATIC_DRAW);
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