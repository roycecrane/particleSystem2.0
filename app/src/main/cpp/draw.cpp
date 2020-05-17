#include <GLES3/gl32.h>
#include <jni.h>
#include "draw.h"
#include "uniform.h"
#include <time.h>
static AssetManager* d_ass=NULL;
static Draw* g_draw = NULL;
static int drawBuff = 0;
static int frame = 0;
static int numPoints =0;
float circlePosX=0;
float circlePosY=0;
clock_t t1,t2;
bool increaseX = true;
float planetX =0.5f;
bool automate = false;
float planetData [3]={0.0f, 0.0f, 0.0f};
float rainbow[3]={0.0f,0.0f,0.0f};
static bool reset_now=false;
int of_hundred = 0;
int count = 0;

float avg_time = 0.0f;
void Draw::transform() {

    if(numPoints == 0)numPoints = d_ass->CircleIndexNum;
    t1=clock();
    glClear(GL_COLOR_BUFFER_BIT);
    planetData[0]= planetX;
    planetData[1]= -0.1f;
    planetData[2]=d_ass->circleRadius;

    if(0.0 > planetX){
        increaseX = true;
    }
    if(planetX >= 2.0){
        increaseX = false;
    }
    if(increaseX)planetX+=0.006f;
    if(!increaseX)planetX-=0.006f;

    d_ass->updateUniform("time", planetData);
    d_ass->updateUniform("seeker",NULL);
    d_ass->updateUniform("touch", NULL);
    d_ass->updateUniform("button", NULL);
    d_ass->updateUniform("time",NULL);


    glUseProgram(d_ass->shaders[0]);
    glEnable(GL_RASTERIZER_DISCARD);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK,d_ass->FBO[drawBuff]);
    glBeginTransformFeedback(GL_POINTS);
    glBindVertexArray(d_ass->VAO[1-drawBuff]);
    glDrawArrays(GL_POINTS, 0, numPoints);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEndTransformFeedback();
    glDisable(GL_RASTERIZER_DISCARD);

}
void Draw::feedBack() {
//    glClearColor(0.0f, 0.0f,0.0f, 0.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
    if(numPoints<d_ass->numIndices&&frame%2==0)numPoints++;
//    d_ass->updateUniform("time",rainbow);
//
    checkGlError("Adraw");
    d_ass->updateUniform("VMat", NULL);
    d_ass->updateUniform("PMat", NULL);
    glUseProgram(d_ass->shaders[1]);
    glBindVertexArray(d_ass->VAO[drawBuff]);
    glDrawArrays(GL_POINTS ,0 ,numPoints);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_ass->updateUniform("VMat2", NULL);
    d_ass->updateUniform("PMat2", NULL);
    d_ass->updateUniform("time2", planetData);
    d_ass->updateUniform("time2",NULL);

    glUseProgram(d_ass->shaders[2]);
    glBindVertexArray(d_ass->VAO2[0]);
    glDrawArrays(GL_TRIANGLES,0,d_ass->numIndices/3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    drawBuff = 1 - drawBuff;
    checkGlError("draw");
    t2=clock();
    float diff ((float)t2-(float)t1);
    frame ++;



    if(reset_now){
        d_ass->resetBuffers();
        reset_now = false;
    }
}
Draw::Draw(AssetManager* ass) {
    d_ass = ass;
    g_draw = this;
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
    g_draw->transform();
    g_draw->feedBack();
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