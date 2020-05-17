#ifndef BUFFERINIT_H
#define BUFFERINIT_H
#include <iostream>
#include <vector>
#include <GLES3/gl32.h>
#include "World.h"
class Buffer{
public:
    float* m_vertcies;
    int m_indexNumber;
    static GLuint totalBufferNumber;
    static GLuint* m_VAO;
    static GLuint* m_FBO;

    bool m_isEmpty;
    GLuint m_bufferID[3];
    GLuint test_vao;
    GLuint m_attributeIndex = 0;
    void fillBuffer();
    void initVAO(int VAONumber, int bufferNum);
    Buffer(float * verticies, int index_number, GLuint * VAO, GLuint * FBO,int numBuffers);
    Buffer(float * verticies, int index_number, GLuint  VAO,int VAONum);
    ~Buffer();

private:
};
#endif //BUFFERINIT_H
