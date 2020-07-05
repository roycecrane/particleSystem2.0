#include <GLES3/gl32.h>
#include <jni.h>
#include "draw.h"
#include "uniform.h"
#include "glm/vec4.hpp"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include <time.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.inl"

static AssetManager* d_ass=NULL;
static Draw* g_draw = NULL;
static int drawBuff = 0;
static int frame = 0;

clock_t t1,t2;
bool increaseX = true;
float planetX = -10.5f;


float planetData [3]={0.0f, 0.0f, 0.0f};
float rainbow[3]={0.0f,0.0f,0.0f};
static bool reset_now=false;
int of_hundred = 0;
int count = 0;
static  float frameTime = 0;
float avg_time = 0.0f;
void Draw::transform() {

//    if (numPoints == 0)numPoints = d_ass->CircleIndexNum;
    numPoints=d_ass->circleIndexNum;
    glClear(GL_COLOR_BUFFER_BIT);
    planetData[0] = -0.0f ;
    planetData[1] = 1.0f;
    planetData[2] = d_ass->circleRadius;

    if (-5.0f > planetX && -7.1f < planetX) {
        increaseX = true;
    }
    if (planetX >= 5.0) {
        increaseX = false;
    }
    if (increaseX)planetX += 0.18f;
    if (!increaseX)planetX -= 0.18f;

    d_ass->updateUniform("time", planetData);
    d_ass->updateUniform("seeker", NULL);
    d_ass->updateUniform("touch", NULL);
    d_ass->updateUniform("button", NULL);
    d_ass->updateUniform("time", NULL);


    glUseProgram(d_ass->shaders[0]);
    glEnable(GL_RASTERIZER_DISCARD);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, d_ass->FBO[drawBuff]);
    glBeginTransformFeedback(GL_POINTS);
    GLfloat *ptr;
    GLfloat *ptr2;
    glBindVertexArray(d_ass->VAO[1 - drawBuff]);
    glDrawArrays(GL_POINTS, 0, numPoints);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEndTransformFeedback();
    if (frame == 1){
        fb = new float[d_ass->numIndices*4];
        fb2 = new float[d_ass->numIndices*4];
        cam = new float[4];
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_ass->buffers[3].m_bufferID[drawBuff]);
    ptr = (GLfloat *) glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * d_ass->circleIndexNum*4,GL_MAP_WRITE_BIT);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    checkGlError("draw");


    if (ptr != nullptr) {
        memcpy(fb, ptr, numPoints*4 * sizeof(float));
        for (int i = 2; i < numPoints*4; i += 4) {
            fb2[i] = fb[132];
            fb2[i+1] = fb[133];
            fb2[i+2] = fb[134];
            fb2[i+3] = fb[135];

        }
        cam[0]=fb[132];
        cam[1]=fb[133];
        cam[2]=fb[134];
        cam[3]=fb[135];
        checkGlError("draw");


        glBindBuffer(GL_ARRAY_BUFFER, d_ass->buffers[3].m_bufferID[1-drawBuff]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, d_ass->circleIndexNum* 4 * sizeof(float), &fb2[0]);

        }
        glDisable(GL_RASTERIZER_DISCARD);
    checkGlError("draw");

    }


void Draw::draw() {
    drawCalls();
    if(numPoints<d_ass->numIndices&&frame%2==0)numPoints++;
    glUseProgram(d_ass->shaders[1]);
    glUniformMatrix4fv(d_ass->mMAT, 1, GL_FALSE, &Model[0][0]);
    glUniformMatrix4fv(d_ass->vMAT, 1, GL_FALSE, &View[0][0]);
    glUniformMatrix4fv(d_ass->pMAT, 1, GL_FALSE, &Projection[0][0]);
    glBindVertexArray(d_ass->VAO[drawBuff]);
    glDrawArrays(GL_POINTS ,0 ,d_ass->circleIndexNum);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    checkGlError("draw");
    drawBuff = 1 - drawBuff;
    checkGlError("draw");
    if(reset_now){
        d_ass->resetBuffers();
        reset_now = false;
    }
}
void Draw::draw2() {
        glm::mat4 Model2 = glm::translate(Model,glm::vec3(2.0f,2.0f,0.0));

//    drawCalls();
    glUseProgram(d_ass->shaders[2]);
    glUniformMatrix4fv(d_ass->mMAT2, 1, GL_FALSE, &Model2[0][0]);
    glUniformMatrix4fv(d_ass->vMAT2, 1, GL_FALSE, &View[0][0]);
    glUniformMatrix4fv(d_ass->pMAT2, 1, GL_FALSE, &Projection[0][0]);
    glBindVertexArray(d_ass->VAO2[0]);
    glDrawArrays(GL_POINTS,0,d_ass->gridIndexNum);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
Draw::Draw(AssetManager* ass){
    d_ass = ass;
    g_draw = this;
}

void Draw::drawCalls() {
    float w,h;
    float angle;
    h= (float)d_ass->d_height;
    w=(float) d_ass->d_width;

    checkGlError("Adraw");
    glm::vec4 camera(cam[0],cam[1],cam[2],cam[3]);
    float camMag = sqrt(cam[2]*cam[2]+cam[3]*cam[3]);

     View = glm::lookAt(
            glm::vec3(0.0f,1.0f, 1.0f),
            glm::vec3(0.0f,0.0f,0.8f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    );
    Model= glm::mat4(1.0f);
   angle = acosf((cam[3]/camMag));
   if(signbit(cam[2])) angle*=-1.0f;
    View = glm::rotate(
            View,
            angle*180/3.14159f,
            glm::vec3(0.0f,0.0f, 1.0f)
    );
    //            __android_log_print(ANDROID_LOG_ERROR, "feedback", "%f", fb[132]);
//             __android_log_print(ANDROID_LOG_ERROR, "feedback", "%f", fb[133]);
//            __android_log_print(ANDROID_LOG_ERROR, "feedback", "%f", fb[134]);
//            __android_log_print(ANDROID_LOG_ERROR, "cam0", "%f", cam[0]);
//    Model = glm::translate(View,glm::vec3(0.0f,0.0f,planetX));

    View = glm::translate(View,glm::vec3(-cam[0],-cam[1],0.0f));
    Projection = glm::perspective(75.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
}

Draw::Draw() {

}

extern "C" {
JNIEXPORT void JNICALL Java_com_android_gles3jni_ParticleSystemLib_reset(JNIEnv* env, jclass obj);
JNIEXPORT void JNICALL Java_com_android_gles3jni_ParticleSystemLib_reset(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_com_android_gles3jni_ParticleSystemLib_step(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_com_android_gles3jni_ParticleSystemLib_inputs(JNIEnv * env , jclass obj, jfloatArray userInput , jstring inputName ) ;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_ParticleSystemLib_step(JNIEnv* env, jclass obj) {

    frame ++;
    frameTime += ((float)t2 - (float)t1);
    if(frame%2000==0){
        float avg = frameTime/(float)frame;
        frame =0;
        frameTime =0.0f;
        __android_log_print(ANDROID_LOG_ERROR, "f/t", "%f",avg);

    }
    t1=clock();
    checkGlError("0draw");

    g_draw->transform();
    g_draw->draw2();
    g_draw->draw();



    checkGlError("2draw");
    t2=clock();

}
extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_ParticleSystemLib_inputs(JNIEnv* env, jclass obj, jfloatArray userInput, jstring inputName) {
    float *InputToCPP = env->GetFloatArrayElements(userInput,0 );
    env->ReleaseFloatArrayElements(userInput,InputToCPP, 0);
    const char *name = env->GetStringUTFChars(inputName, 0);
    env->ReleaseStringUTFChars(inputName,name);
d_ass->updateUniform(name,InputToCPP);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_ParticleSystemLib_reset(JNIEnv* env, jclass obj) {
    ALOGE("reset");
    reset_now = true;
}
//    unsigned size = (float)env->GetArrayLength(userInput);



