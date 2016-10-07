#ifndef ESTUDOSOPENGL_ARRAYBUFFER_H
#define ESTUDOSOPENGL_ARRAYBUFFER_H

class ArrayBuffer {
public:
	ArrayBuffer();
    ArrayBuffer(int _totalBytes, float *data);
    ~ArrayBuffer(){}
    void bind();
    void unbind();
    void draw();

    GLuint id;
    int totalBytes;
    int numElements;
};

#endif //ESTUDOSOPENGL_ARRAYBUFFER_H
