#include <OpenGL/gl3.h>
#include <stdexcept>

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(int _totalBytes, float *data) {
    if (_totalBytes < 1) {
		throw std::invalid_argument("Cannot create Index Buffer. Number of bytes must be bigger then 0." );
    }
    if (data == NULL) {
    	throw std::invalid_argument("Cannot create Index Buffer. Data cannot be null.");
    }
    
	totalBytes = _totalBytes;
    numElements = totalBytes / sizeof(float);

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
	glDrawArrays(GL_TRIANGLES, 0, numElements);	
}