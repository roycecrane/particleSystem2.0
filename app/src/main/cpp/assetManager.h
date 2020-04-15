#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <iostream>
#include <GLES3/gl32.h>
#include "World.h"
#include "uniform.h"
#include "BufferInit.h"

class AssetManager{
public:
    AssetManager();
    ~AssetManager();
    void resetBuffers();
    void initBuffs();
    void initShaderPrograms();
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
     GLuint* FBO;
     int numIndices;
};




#endif //ASSETMANAGER_H

