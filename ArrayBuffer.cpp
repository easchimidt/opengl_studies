#include <OpenGL/gl3.h>
#include <stdexcept>

#include "ArrayBuffer.h"

ArrayBuffer::ArrayBuffer(int _element_size, const std::vector<float>& data) {
    if (data.size() < 1) {
		throw std::invalid_argument("Cannot create Array Buffer. Number of bytes must be bigger then 0." );
    }

    element_size = _element_size;
    total_bytes = data.size() * sizeof(float);
    num_elements = data.size();

    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ARRAY_BUFFER, total_bytes, &data[0], GL_STATIC_DRAW);
    unbind();
}

void ArrayBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void ArrayBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ArrayBuffer::draw() {
	glDrawArrays(GL_TRIANGLES, 0, num_elements);
}