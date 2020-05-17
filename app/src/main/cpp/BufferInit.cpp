#include "BufferInit.h"
#include "errorChecker.h"
GLuint* Buffer:: m_VAO;
GLuint* Buffer::m_FBO;
GLuint Buffer::totalBufferNumber = 0;
Buffer::Buffer(float * verticies, int index_number,GLuint * VAO, GLuint * FBO, int numBuffers)
{

    m_vertcies = verticies;
    checkGlError("VAO");
    m_indexNumber= index_number * 3;
    m_VAO = VAO;
    m_FBO = FBO;
    m_attributeIndex = totalBufferNumber;
    totalBufferNumber++;
    glGenBuffers(numBuffers,m_bufferID);
        for (int i = 0; i < numBuffers; ++i) {
            initVAO(i,i);
        }
}

Buffer::Buffer(float * verticies, int index_number,GLuint  VAO, int VAONum){
    m_vertcies = verticies;
    m_indexNumber= index_number * 3;
    test_vao = VAO;
    m_FBO = NULL;
    glGenBuffers(1,&m_bufferID[0]);
    m_attributeIndex = 0;
    totalBufferNumber++;
    initVAO(VAONum,0);
}


void Buffer::initVAO(int VAONumber,int bufferNum ){
    //buffer NULL values
//    __android_log_print(ANDROID_LOG_ERROR, "vtx", "%f",planetX);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[bufferNum]);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_indexNumber * sizeof(float)), NULL, GL_DYNAMIC_COPY);
    //buffer given values
    if(m_vertcies!=NULL) {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[bufferNum]);
        glBufferSubData(GL_ARRAY_BUFFER, 0 ,(m_indexNumber * sizeof(float)), &m_vertcies[0]);
    }
    if(VAONumber== 3){
        glBindVertexArray(test_vao);
    } else glBindVertexArray(m_VAO[VAONumber]);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[bufferNum]);
    glVertexAttribPointer(m_attributeIndex, 3, GL_FLOAT, GL_FALSE,  sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(m_attributeIndex);
    glBindVertexArray(0);
    if(m_FBO != NULL){
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_FBO[VAONumber]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, m_attributeIndex, m_bufferID[VAONumber]);

    }
}

void Buffer::fillBuffer() {
    if(m_vertcies!=NULL) {
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0 ,(m_indexNumber * sizeof(float)), &m_vertcies[0]);


    }
}
Buffer::~Buffer() {
}







