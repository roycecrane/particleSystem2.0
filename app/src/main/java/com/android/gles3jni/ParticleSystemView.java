package com.android.gles3jni;
import android.content.Context;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.opengl.Matrix;
import android.view.MotionEvent;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class ParticleSystemView extends GLSurfaceView {
    private static final String TAG = "Particles1.0";
    private static final boolean DEBUG = true;
    static float[] inputArray = {0.0f,0.0f,0.0f};
    static int m_width;
    static int m_height;
    static float x=0.0f;
    static float y=0.0f;
    static float width  = (float)m_width;
    static float height =(float)m_height;

    public ParticleSystemView(Context context, AttributeSet attribs) {

        super(context);
        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(3);
        setRenderer(new Renderer());
    }
    private static class Renderer implements GLSurfaceView.Renderer {
        private final float[] pMat = new float[16];
        private final float[] vPMatrix = new float[16];
        private final float[] vMat = new float[16];

        public void onDrawFrame(GL10 gl) {
            float ratio = (float) m_width / (float)m_height;
            GLES30.glViewport(0, 0, m_width, m_height);
            Matrix.frustumM(pMat, 0, -ratio, ratio, -1, 1, 1, 300);
            Matrix.setLookAtM(vMat, 0, 0.1f, 0.1f, -2.0f, 0.1f, 0.1f, 0f, 1f, -0f, 5f);
//            Matrix.multiplyMM(vPMatrix, 1, pMat, 1, vMat, 1);
            ParticleSystemLib.inputs(pMat,"PMat");
            ParticleSystemLib.inputs(vMat,"VMat");
            ParticleSystemLib.step();
        }
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            m_width  = width;
            m_height = height;
            float ratio = (float) width / (float)height;
            GLES30.glViewport(0, 0, width, height);
            Matrix.frustumM(pMat, 0, -ratio, ratio, -1, 1, 1, 300);
            int [] dispXY = new int[]{width, height};
            ParticleSystemLib.init();
            ParticleSystemLib.sendString( MyStuff.getData2());
            ParticleSystemLib.sendString( MyStuff.getData4());
            ParticleSystemLib.sendString( MyStuff.getData1());
            ParticleSystemLib.sendString( MyStuff.getData3());
            ParticleSystemLib.buildRenderer(dispXY);
            ParticleSystemLib.inputs(vMat,"VMat");
        }
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        if(e.getAction() == MotionEvent.ACTION_DOWN){
            y = e.getY();
            x = e.getX();
        }
        if(e.getAction() == MotionEvent.ACTION_MOVE){
            y = e.getY();
            x = e.getX();
        }

//        if(e.getAction() == MotionEvent.ACTION_UP){}
//        if(e.getAction() == MotionEvent.ACTION_CANCEL){}
        inputArray[0] = -0.5f+(x -width/2.0f)/(float)m_width;
        inputArray[1] = 0.5f-(y- height/2.0f)/(float)m_height;
        inputArray[0]*= 2.0f;
        inputArray[1]*= 2.0f;
        ParticleSystemLib.inputs(inputArray,"touch");
        return true;
        }
    }

