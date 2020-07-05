#include "uniform.h"
#include "errorChecker.h"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/gtc/type_ptr.inl"

int Uniform::numUniforms = 0;
Uniform::Uniform(GLuint progID, std::string name,const char*type,bool isAutomated) {
    m_name = name;
    m_isAutomated = isAutomated;
    m_type = type;
    m_progID = progID;
    m_ID = numUniforms;
    numUniforms += 1;

    m_uniformID = (glGetUniformLocation(progID, m_name.c_str()));

    if(strcmp(type ,"MAT4")==0){
        m_data = new float[16]{0};
        m_length = 16;
    };
    if(strcmp(type ,"VEC3")==0)
    {
        m_data = new float[3]{0};
        m_length = 3;
    };

}
void Uniform::setUniform(const char* type, float* data){

        if(data != NULL ){
            for (int i = 0; i < m_length ; ++i) {
                m_data[i] = data[i];
            }
        }else {

            if (strcmp(type, "ALREADY_SET") == 0) type = m_type;
            glUseProgram(m_progID);

                if (strcmp(type, "MAT4") == 0) glUniformMatrix4fv(m_uniformID, 1, GL_FALSE, m_data);
                if (strcmp(type, "VEC3") == 0){
                    if(!m_isAutomated) {
                        glUniform3f(m_uniformID, m_data[0], m_data[1], m_data[2]);
                }
            }
            glUseProgram(0);
        }
        if(m_name=="seeker"){

        }

}
void Uniform::setUniform(const char* type, glm::mat4 &glmMatrix){



}
void Uniform::automate(float* data){
    static float timeBackwards;
    static float stepSize = 0.002;
    float max = 1.0;
    float min = -1.0f;
    static bool isStepPositive;
    static float counterA;
    if(m_frame==0){
        timeBackwards = 1.0;
        isStepPositive = true;
        counterA =min;
    }
    if(m_frame % 2 == 0){
        if(counterA < max +  stepSize && counterA >= max) {
//            counterA=min;
            isStepPositive = false;
            timeBackwards *=-1.0f;
        }
        if(counterA > min -  stepSize && counterA <= min ){
            isStepPositive = true;
            timeBackwards *=-1.0f;
        }
        if(isStepPositive)counterA += stepSize;
        if(!isStepPositive)counterA -= stepSize;
    }


    glUseProgram(m_progID);
    glUniform3f(m_uniformID,counterA,data[1],data[2] );
    glUseProgram(0);
    m_frame++;
}

void Uniform::setAutomated() {
m_isAutomated = true;
}










