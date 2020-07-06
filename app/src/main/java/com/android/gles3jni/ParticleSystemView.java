package com.android.gles3jni;
import android.content.Context;
import android.content.res.Resources;
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
    static float touchX = 0.0f;
    static float touchY = 0.0f;
    static int m_width;
    static int m_height;
    static float width = 0.0f;
    static float height = 0.0f;
    static int[] dispXY = {0,0};
    public static int getScreenWidth() {
        return Resources.getSystem().getDisplayMetrics().widthPixels;
    }

    public static int getScreenHeight() {
        return Resources.getSystem().getDisplayMetrics().heightPixels;
    }
    public ParticleSystemView(Context context, AttributeSet attribs) {

        super(context);
        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(3);
        dispXY[0] = getScreenWidth();
        dispXY[1] = getScreenHeight();
        setRenderer(new Renderer());
    }
    private static class Renderer implements GLSurfaceView.Renderer {
        private final float[] pMat = new float[16];
        private final float[] vMat = new float[16];
        public void onDrawFrame(GL10 gl) {

            ParticleSystemLib.step();
        }
        void perspective(){
            int m_width  = getScreenWidth();
            int m_height = getScreenHeight();
            float ratio = (float) m_width / (float)m_height;
            GLES30.glViewport(0, 0, m_width, m_height);
//            Matrix.frustumM(pMat, 0, -ratio, ratio, -1, 1, 1, 100);
//            Matrix.setLookAtM(vMat, 0,
//                    0, -5, 9,
//                    0f, 1f, 4f,
//                    0f, 3.0f, 1.0f);
//
//            ParticleSystemLib.inputs(pMat,"PMat");
//            ParticleSystemLib.inputs(vMat,"VMat");
//            ParticleSystemLib.inputs(pMat,"PMat2");
//            ParticleSystemLib.inputs(vMat,"VMat2");
        }
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            ParticleSystemLib.init();
            ParticleSystemLib.sendString( MyStuff.getData1());
            ParticleSystemLib.sendString( MyStuff.getData2());
            ParticleSystemLib.sendString( MyStuff.getData3());
            ParticleSystemLib.sendString( MyStuff.getData4());
            ParticleSystemLib.sendString( MyStuff.getData5());
            ParticleSystemLib.sendString( MyStuff.getData6());

            ParticleSystemLib.buildRenderer(dispXY[0],dispXY[1]);
            perspective();
        }
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        if(e.getAction() == MotionEvent.ACTION_DOWN){
            touchY = e.getY();
            touchX = e.getX();
        }
        if(e.getAction() == MotionEvent.ACTION_MOVE){
            touchY = e.getY();
            touchX = e.getX();
        }
//        if(e.getAction() == MotionEvent.ACTION_UP){}
//        if(e.getAction() == MotionEvent.ACTION_CANCEL){}
//        inputArray[0] =-(touchX -(float)m_width/2.0f)/(float)m_width;
//        inputArray[1] = -(touchY- (float)m_height/2.0f)/(float)m_height;
        inputArray[0] = (touchX -(float)m_width/2.0f)/(float)m_width;
        inputArray[1] = -(touchY- (float)m_height/2.0f)/(float)m_height;

        inputArray[0]*= 4.0f;
        inputArray[1]*= 6.0f;
        ParticleSystemLib.inputs(inputArray,"touch");
        return true;
        }
    }

