package com.android.gles3jni;

// Wrapper for native library

public class ParticleSystemLib {
     static {
          System.loadLibrary("gles3jni");
     }
     public static native void init();
     public static native void inputs(float[]userInput,String inputName);
     public static native void buildRenderer(int[]displayDimension);
     public static native void step();
     public static native void reset();
     public static native void sendString(String shaderFile);


}

