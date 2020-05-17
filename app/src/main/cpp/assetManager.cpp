#include "assetManager.h"
#include "errorChecker.h"

#include "shader.h"
static std::vector<Uniform>  uniforms;

void AssetManager::updateUniform(std::string uniName,float *data) {
    for (int i = 0; i < uniforms.size() ; ++i) {
        if(uniforms[i].m_name == uniName.c_str()){
//            __android_log_print(ANDROID_LOG_ERROR, "found", "%s",uniName.c_str());
            uniforms[i].setUniform("ALREADY_SET",data);

            break;
        }
    }
    checkGlError("uniformsEnd");

}
AssetManager::AssetManager() {


}

void AssetManager::initShaderPrograms() {
    Shader shader;
    const GLchar* FBVayrings[4] = {"pos_out", "vel_out", "FBDAT_out","initPos_out"};
    shaders.push_back(shader.getShaderProgram(files[0], files[1], FBVayrings));
    shaders.push_back(shader.getShaderProgram(files[2], files[3], NULL));
    shaders.push_back(shader.getShaderProgram(files[4], files[5], NULL));
}

void AssetManager::initWorld(int *dispXY){


    particleSystem p = particleSystem(vertcies,velocities,dispXY);

    World* world;
    world = &p;
    numIndices = world->setPositions();

    vertcies = new float[numIndices];
    velocities = new float[numIndices];

    vertcies = world->getPositions();
    velocities = world->initVelocities();

    CircleIndexNum = p.circleIndexNum;
    circleRadius = p.radius;
}

void AssetManager::initBuffs(){
    FBO = new GLuint[2];
    VAO = new GLuint[2];
    VAO2 = new GLuint[2];
    glGenVertexArrays(1,VAO2);

    glGenVertexArrays(3,VAO);
    glGenTransformFeedbacks(2, FBO);
    checkGlError("initb0");
    buffers.push_back(Buffer( vertcies ,numIndices,VAO,FBO,2));
    checkGlError("initb1");
    buffers.push_back(Buffer( velocities ,numIndices,VAO,FBO,2));
    buffers.push_back(Buffer( NULL ,numIndices,VAO,FBO,2));
    buffers.push_back(Buffer( vertcies ,numIndices,VAO,FBO,2));
    GLuint  buffer;


    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER,buffer);
//    glBufferData(GL_ATOMIC_COUNTER_BUFFER, static_cast<GLsizeiptr>(3*numIndices * sizeof(float)), NULL, GL_DYNAMIC_COPY);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
//    buffers[0].totalBufferNumber = 0;
    buffers.push_back(Buffer(vertcies,numIndices,VAO2[0],3));

    checkGlError("initBuffers");

}
void AssetManager::initUniforms(){
    uniforms.push_back(Uniform(shaders[0], "time", "VEC3",false));
    uniforms.push_back(Uniform(shaders[0], "touch", "VEC3",false));
    uniforms.push_back(Uniform(shaders[0], "seeker","VEC3",true));
    uniforms.push_back(Uniform(shaders[0], "button","VEC3",false));
    uniforms.push_back(Uniform(shaders[1], "VMat", "MAT4",false));
    uniforms.push_back(Uniform(shaders[1], "PMat", "MAT4",false));
    uniforms.push_back(Uniform(shaders[2], "time2", "VEC3",false));
    uniforms.push_back(Uniform(shaders[2], "VMat2", "MAT4",false));
    uniforms.push_back(Uniform(shaders[2], "PMat2", "MAT4",false));

    checkGlError("initUniforms");

}
void AssetManager::resetBuffers(){
    for(int i = 0; i < buffers.size(); ++i) buffers[i].fillBuffer();
}
AssetManager::~AssetManager() {
//    delete[]velocities;
//    delete[]vertcies;
}




