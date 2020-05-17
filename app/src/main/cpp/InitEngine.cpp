#include <math.h>
#include <vector>
#include <string>
#include <GLES3/gl32.h>
#include<string>
#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "assetManager.h"
#include "draw.h"
#include "errorChecker.h"

static AssetManager* g_assMan = NULL;
static Draw* g_draw = NULL;

#if !defined(DYNAMIC_ES3)
static GLboolean gl3stubInit() {
    return GL_TRUE;
}
#endif

extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_ParticleSystemLib_init(JNIEnv* env, jclass obj, jintArray jDimension) {
    const char* versionStr = (const char*)glGetString(GL_VERSION);
    const char* versionStrMInor = (const char*)glGetString(GL_MINOR_VERSION);
    ALOGE("GL_MINOR:\n%s\n",versionStr,
          versionStr);
    if (strstr(versionStr, "OpenGL ES 3.") ) {
        ALOGE("GL VER 3.");

    } else if (strstr(versionStr, "OpenGL ES 2.")) {
        ALOGE("GL VER 2");
    } else {
        ALOGE("Unsupported OpenGL ES version");
    }

    if(g_assMan) delete g_assMan;
    if(g_draw) delete g_draw;

    g_assMan = new AssetManager();
    g_draw = new Draw(g_assMan);
    ALOGE("test");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_ParticleSystemLib_sendString(JNIEnv *env, jclass obj, jstring stringIn){
    const char *stringOut = env->GetStringUTFChars(stringIn, 0);
    env->ReleaseStringUTFChars(stringIn,stringOut);
    g_assMan->files.push_back(stringOut);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_ParticleSystemLib_buildRenderer(JNIEnv *env, jclass obj,jintArray jDispXy) {

    int *dispXY = env->GetIntArrayElements(jDispXy, NULL);
    env->ReleaseIntArrayElements(jDispXy,dispXY,  0);
    if(g_assMan->files.empty()) {
        ALOGE("No shader files loaded");
    }
    g_assMan->initShaderPrograms();
    checkGlError("initShader");
    g_assMan->initUniforms();
    checkGlError("initUni");

    g_assMan->initWorld(dispXY);
    checkGlError("initWorld");


    g_assMan->initBuffs();
    checkGlError("initBuff");

}