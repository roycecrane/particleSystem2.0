#ifndef UNIFORM_H
#define UNIFORM_H
#include <string>
#include <vector>
#include <GLES3/gl32.h>
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_mat4x4.hpp"

class Uniform{
public:
    int m_frame = 0;
    bool m_isAutomated = false;
    static int numUniforms;
    static std::vector<std::string> nameList;
    float* m_data;
    std::string m_name;
    int m_ID;
    int m_length;
    glm::mat4  m_glmMatrix;

    const char* m_type;
    GLuint m_progID;
    GLint m_uniformID;
        void setUniform(const char* type, glm::mat4& glmMatrix);
        Uniform(GLuint progID, std::string name,const char* type,bool isAutomated);
    void setUniform(const char* type,float* data);
    void automate(float* data);
    void setAutomated();
};




#endif //UNIFORM_H
