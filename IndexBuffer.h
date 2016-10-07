#ifndef ESTUDOSOPENGL_INDEXBUFFER_H
#define ESTUDOSOPENGL_INDEXBUFFER_H

class IndexBuffer {
public:
	IndexBuffer();
    IndexBuffer(int _totalBytes, float *data);
    ~IndexBuffer(){}
    void bind();
    void unbind();
    void draw();

    GLuint id;
    int totalBytes;
    int numElements;
};

#endif //ESTUDOSOPENGL_INDEXBUFFER_H
