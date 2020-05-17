#ifndef UNIFORM_H
#define UNIFORM_H
#include <string>
#include <vector>
#include <GLES3/gl32.h>
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
    const char* m_type;
    GLuint m_progID;
    GLint m_uniformID;
    Uniform(GLuint progID, std::string name,const char* type,bool isAutomated);
    void setUniform(const char* type,float* data);
    void automate(float* data);
    void setAutomated();
};




#endif //UNIFORM_H
