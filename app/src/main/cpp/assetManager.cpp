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
void AssetManager::updateUniform(std::string uniName,glm::mat4& data){
    for (int i = 0; i < uniforms.size() ; ++i) {
        if(uniforms[i].m_name == uniName.c_str()){
            uniforms[i].setUniform("ALREADY_SET",data);
            checkGlError("initBuffers");
            checkGlError("initBuffers");

            break;
        }
    }
    checkGlError("uniformsEnd");

}
AssetManager::AssetManager() {


}

void AssetManager::initShaderPrograms() {
    Shader shader;

    const GLchar* FBVayrings[4] = {"pos_out", "vel_out", "FBDAT_out","camera_out"};
    shaders.push_back(shader.getShaderProgram(files[0], files[1], FBVayrings));
    checkGlError("0");
    shaders.push_back(shader.getShaderProgram(files[2], files[3], NULL));
    checkGlError("1");
    shaders.push_back(shader.getShaderProgram(files[4], files[5], NULL));
    checkGlError("2");
}

void AssetManager::initWorld(int *dispXY){
    d_width = dispXY[0];
    d_height= dispXY[1];

   Grid grid = Grid(dispXY,0);
    grid.setPositions(gridVerts);
    Circle circle = Circle(dispXY,0);
    circle.setPositions(circleVerts);
    circle.initVelocities(circleVels);
    circleVels[101]=3.0f;
    circleVerts[99]=0.0f;
    circleVerts[100]=-1.05f;
    circleIndexNum = circle.index_number;
    circleRadius = circle.radius;
    gridIndexNum = grid.index_number;
    numIndices = circle.index_number;

}

void AssetManager::initBuffs(){
    FBO = new GLuint[2];
    VAO = new GLuint[3];
    VAO2 = new GLuint[1];

    glGenVertexArrays(1,VAO2);

    glGenVertexArrays(2,VAO);
    glGenTransformFeedbacks(2, FBO);
    checkGlError("initb0");
    buffers.push_back(Buffer( circleVerts,3 ,circleIndexNum*3,VAO,FBO,2));
    buffers.push_back(Buffer( circleVels,3 ,circleIndexNum*3,VAO,FBO,2));
    buffers.push_back(Buffer( std::vector<float>{} ,3 ,circleIndexNum*3,VAO,FBO,2));
    buffers.push_back(Buffer( std::vector<float> {},4 ,circleIndexNum*4,VAO,FBO,2));
    buffers.push_back(Buffer( circleVerts,3 ,circleIndexNum*3,VAO,NULL,2));
    mMAT = (glGetUniformLocation(shaders[1], "mMAT"));
    vMAT = (glGetUniformLocation(shaders[1], "vMAT"));
    pMAT = (glGetUniformLocation(shaders[1], "pMAT"));
    {
        GLuint * buff = new GLuint[1];
        glGenBuffers(1,buff);
        glBindBuffer(GL_ARRAY_BUFFER, buff[0]);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(3*gridIndexNum * sizeof(float)), NULL, GL_DYNAMIC_COPY);
        glBindBuffer(GL_ARRAY_BUFFER,buff[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (gridIndexNum*3 * sizeof(float)), &gridVerts[0]);
        glBindVertexArray(VAO2[0]);
        glBindBuffer(GL_ARRAY_BUFFER, buff[0]);
        glVertexAttribPointer(buffers[0].m_attributeIndex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *) 0);
        glEnableVertexAttribArray(buffers[0].m_attributeIndex);
    }
//    buffers.push_back(Buffer( vertcies,3 ,numIndices*3,VAO,NULL,2 ));
    mMAT2 = (glGetUniformLocation(shaders[2], "mMAT2"));
    vMAT2 = (glGetUniformLocation(shaders[2], "vMAT2"));
    pMAT2 = (glGetUniformLocation(shaders[2], "pMAT2"));

    counters = new GLuint [1];
    counters[0]=0;
    counters[1]=1;

//    glGenBuffers(1,&atomicBuffer);
//    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER,atomicBuffer);
//    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_DYNAMIC_DRAW);
//    glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, counters[0]);


//    buffers[0].totalBufferNumber = 0;
//    buffers.push_back(Buffer(vertcies,numIndices,VAO2[0],3));

    checkGlError("initBuffers");

}
void AssetManager::initUniforms(){
    uniforms.push_back(Uniform(shaders[0], "time", "VEC3",false));
    uniforms.push_back(Uniform(shaders[0], "touch", "VEC3",false));
    uniforms.push_back(Uniform(shaders[0], "seeker","VEC3", false));
    uniforms.push_back(Uniform(shaders[0], "button","VEC3",false));

    checkGlError("initUniforms");

}
void AssetManager::resetBuffers(){
    for(int i = 0; i < buffers.size(); ++i) buffers[i].fillBuffer();
}
AssetManager::~AssetManager() {
//    delete[]circleVels;
//    delete[]vertcies;
}




