#include "BufferInit.h"
#include "errorChecker.h"
GLuint* Buffer:: m_VAO;
GLuint* Buffer::m_FBO;
GLuint Buffer::totalBufferNumber = 0;
Buffer::Buffer(std::vector<float> verticies,int size, int index_number,GLuint * VAO, GLuint * FBO, int numBuffers)
{
    m_vertcies = verticies;
    checkGlError("VAO");
    m_indexNumber= index_number;
    m_VAO = VAO;
    m_FBO = FBO;
    m_attributeIndex = totalBufferNumber;
    totalBufferNumber++;
    glGenBuffers(2,m_bufferID);
            initVAO(size,2);

}
Buffer::Buffer(std::vector<float> verticies,int size, int index_number,GLuint * VAO)
{
    m_vertcies = verticies;
    checkGlError("VAO");
    m_indexNumber= index_number;
    m_VAO = VAO;
    m_FBO = NULL;
    m_attributeIndex = totalBufferNumber;
    totalBufferNumber++;
    glGenBuffers(1,m_bufferID);
    initVAO(size,1);

}
void Buffer::initVAO(int size,int bufferNum  ){

        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[0]);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_indexNumber * sizeof(float)), NULL, GL_DYNAMIC_COPY);
        if(bufferNum==2){
            glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[1]);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_indexNumber * sizeof(float)), NULL, GL_DYNAMIC_COPY);
        }

    if(!m_vertcies.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (m_indexNumber * sizeof(float)), &m_vertcies[0]);
        if(bufferNum==2){
            glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[1]);
            glBufferSubData(GL_ARRAY_BUFFER, 0 ,(m_indexNumber * sizeof(float)), &m_vertcies[0]);
        }

    }
    if(m_attributeIndex ==5 ) {

        }
    glBindVertexArray(0);
        glBindVertexArray(m_VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[0]);
        glVertexAttribPointer(m_attributeIndex, size, GL_FLOAT, GL_FALSE,  sizeof(float) *size, (void*)0);
        glEnableVertexAttribArray(m_attributeIndex);
        glBindVertexArray(0);
        if(bufferNum==2) {
            glBindVertexArray(m_VAO[1]);
            glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[1]);
            glVertexAttribPointer(m_attributeIndex, size, GL_FLOAT, GL_FALSE, sizeof(float) * size,(void *) 0);
            glEnableVertexAttribArray(m_attributeIndex);
            glBindVertexArray(0);
        }

    if(m_FBO != NULL) {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_FBO[0]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, m_attributeIndex, m_bufferID[0]);
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_FBO[1]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, m_attributeIndex, m_bufferID[1]);
    }
}


void Buffer::fillBuffer() {
    if(!m_vertcies.empty()) {
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0 ,(m_indexNumber * sizeof(float)), &m_vertcies[0]);
    }
}
Buffer::~Buffer() {
}







