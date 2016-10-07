#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdexcept>

#include "ArrayBuffer.h"

ArrayBuffer::ArrayBuffer(int _totalBytes, float *data) {
    if (_totalBytes < 1) {
		throw std::invalid_argument("Cannot create Array Buffer. Number of bytes must be bigger then 0." );
    }
    if (data == NULL) {
    	throw std::invalid_argument("Cannot create Array Buffer. Data cannot be null.");
    }
    
	totalBytes = _totalBytes;
    numElements = totalBytes / sizeof(float);

    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ARRAY_BUFFER, totalBytes, data, GL_STATIC_DRAW);
    unbind();
}

void ArrayBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void ArrayBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ArrayBuffer::draw() {
	glDrawArrays(GL_TRIANGLES, 0, numElements);	
}