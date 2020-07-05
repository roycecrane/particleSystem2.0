#ifndef BUFFERINIT_H
#define BUFFERINIT_H
#include <iostream>
#include <vector>
#include <GLES3/gl32.h>
#include "World.h"
class Buffer{
public:
    std::vector<float> m_vertcies;
    int m_indexNumber;
    static GLuint totalBufferNumber;
    static GLuint* m_VAO;
    static GLuint* m_FBO;

    bool m_isEmpty;
    GLuint m_bufferID[3];
    GLuint test_vao;
    GLuint m_attributeIndex = 0;
    void fillBuffer();
    void initVAO( int size,int VAONumber);
    Buffer(std::vector<float> verticies, int size,int index_number, GLuint * VAO);
    Buffer(std::vector<float> verticies, int size,int index_number, GLuint * VAO, GLuint * FBO,int numBuffers);
    ~Buffer();

private:
};
#endif //BUFFERINIT_H
