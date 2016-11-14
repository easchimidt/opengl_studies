#ifndef ESTUDOSOPENGL_ARRAYBUFFER_H
#define ESTUDOSOPENGL_ARRAYBUFFER_H

#include <vector>

class ArrayBuffer {
public:
	ArrayBuffer();
    ArrayBuffer(int _element_size, const std::vector<float>& data);
    ~ArrayBuffer(){}
    void bind();
    void unbind();
    void draw();

    GLuint id;
    int total_bytes;
    int num_elements;
	int element_size;
};

#endif //ESTUDOSOPENGL_ARRAYBUFFER_H
