#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <iostream>
#include <GLES3/gl32.h>
#include "World.h"
#include "uniform.h"
#include "BufferInit.h"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_mat4x4.hpp"

class AssetManager{
public:
    float circleRadius;
    int circleIndexNum;
    int gridIndexNum;

    std::vector<float> vertcies;
    float * camera;
    std::vector<float> velocities;
    std::vector<float> circleVerts;
    std::vector<float> circleVels;
    std::vector<float> gridVerts;

    AssetManager();
    ~AssetManager();
    void resetBuffers();
    void initBuffs();
    int d_height;
    int d_width;
    GLint  mMAT;
    GLint  vMAT;
    GLint  pMAT;
    GLint  mMAT2;
    GLint  vMAT2;
    GLint  pMAT2;
    GLint  cam;
    GLint  cam2;

    void initShaderPrograms();
    void updateUniform(std::string uniName,glm::mat4& data);

    void updateUniform(std::string uniName,float *data);
    void initWorld(int* dispXY);
    void initUniforms();
    std::vector<Uniform>  uniforms;
    std::vector<Buffer> buffers;
    std::vector<std::string> files;
    std::vector<GLuint> shaders;
    float * pos;
    float * vel;
     GLuint* VAO;
    GLuint* VAO2;
    GLuint* counters;
    GLuint  atomicBuffer;

     GLuint* FBO;
     GLuint* triangleVAO;

     int numIndices;
};




#endif //ASSETMANAGER_H

