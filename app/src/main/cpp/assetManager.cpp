#include "assetManager.h"
#include "errorChecker.h"
#include "shader.h"
#define SHAPE_X 200
#define SHAPE_Y 500
static std::vector<Uniform>  uniforms;

void AssetManager::updateUniform(std::string uniName,float *data) {

    for (int i = 0; i < uniforms.size() ; ++i) {
        if(uniforms[i].m_name == uniName.c_str()){
//            __android_log_print(ANDROID_LOG_ERROR, "found", "%s",uniName.c_str());
            uniforms[i].setUniform("ALREADY_SET",data);
            break;
        }
        if(i == uniforms.size()){
//            __android_log_print(ANDROID_LOG_ERROR, "not found", "%s",uniName.c_str());
        }
    }
    checkGlError("uniformsEnd");

}

AssetManager::AssetManager() {
    numIndices = SHAPE_X * SHAPE_Y;
    pos = new float[numIndices];
    vel = new float[numIndices];
}

void AssetManager::initShaderPrograms() {
    Shader shader;
    const GLchar* FBVayrings[4] = {"P", "V", "O","IP"};
    shaders.push_back(shader.getShaderProgram(files[2], files[1], FBVayrings));
    shaders.push_back(shader.getShaderProgram(files[0], files[3], NULL));
}
void AssetManager::initUniforms(){
    uniforms.push_back(Uniform(shaders[0], "touch", "VEC3"));
    uniforms.push_back(Uniform(shaders[0], "seeker", "VEC3"));
    uniforms.push_back(Uniform(shaders[0], "button", "VEC3"));
    uniforms.push_back(Uniform(shaders[1], "VMat", "MAT4"));
    uniforms.push_back(Uniform(shaders[1], "PMat", "MAT4"));
}
void AssetManager::resetBuffers(){
    for(int i = 0; i < buffers.size(); ++i) buffers[i].fillBuffer();
}
void AssetManager::initWorld(int *dispXY){

    particleSystem p = particleSystem(pos, vel, SHAPE_X, SHAPE_Y,dispXY);
    World* world;
    world = &p;
    world->initMeshData();
}
void AssetManager::initBuffs(){
    FBO = new GLuint[2];
    VAO = new GLuint[2];
    buffers.push_back(Buffer( pos, numIndices, VAO, FBO));
    buffers.push_back(Buffer( vel, numIndices, VAO, FBO));
    buffers.push_back(Buffer( NULL, numIndices, VAO, FBO));
    buffers.push_back(Buffer( pos, numIndices, VAO, FBO));
}
AssetManager::~AssetManager() {
    delete[]pos;
    delete[]vel;
}




