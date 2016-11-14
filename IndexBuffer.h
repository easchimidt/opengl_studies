#ifndef ESTUDOSOPENGL_INDEXBUFFER_H
#define ESTUDOSOPENGL_INDEXBUFFER_H

#include <vector>

class IndexBuffer {
public:
	IndexBuffer();
    IndexBuffer(const std::vector<int>& data);
    ~IndexBuffer(){}
    void bind();
    void unbind();
    void draw();

    GLuint id;
    int totalBytes;
    int numElements;
};

#endif //ESTUDOSOPENGL_INDEXBUFFER_H
