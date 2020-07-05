package com.android.gles3jni;
import android.app.Activity;
import android.os.Bundle;
import android.util.AttributeSet;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;

public class ParticleSystem extends Activity {
    SeekBar seekBar;
    SeekBar seekBar2;
    float[] seekerInput = {1.0f,0.0f,0.0f};
    String seekerName = "seeker";

    private long startTime;
    ParticleSystemView mView;

    float [] buttonPressed ={1.0f,1.0f,-0.25f};
    @Override protected void onCreate(Bundle icicle) {
        MyStuff myobj;
        new MyStuff(ParticleSystem.this);
        super.onCreate(icicle);
        startTime = System.currentTimeMillis();
        setContentView(R.layout.layout);

        mView = (ParticleSystemView) findViewById(R.id.GLES3JNIView2);
        AttributeSet attribs = null;

        mView = new ParticleSystemView(getApplication(), attribs);
        Button mButton = findViewById(R.id.button);
        Button mButton2 = findViewById(R.id.button2);
        Button mButton3 = findViewById(R.id.button3);
        mButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                buttonPressed[0] *= -1.0f;

                ParticleSystemLib.reset();
            }
        });
        mButton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                buttonPressed[1] *= -1.0f;
                buttonPressed[2] = -0.1f;

                ParticleSystemLib.inputs(buttonPressed,"button");

            }
        });
        mButton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                buttonPressed[2] += 0.1f;


                ParticleSystemLib.inputs(buttonPressed,"button");
            }
        });
        seekBar=(SeekBar)findViewById(R.id.seekBar);
        seekBar2=(SeekBar)findViewById(R.id.seekBar2);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                seekerInput[1] = (float)progress;
                ParticleSystemLib.inputs(seekerInput,"seeker");
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                ParticleSystemLib.inputs(seekerInput,seekerName);
            }
        });
        seekBar2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                seekerInput[0] = (float)progress;
                ParticleSystemLib.inputs(seekerInput,"seeker");
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                ParticleSystemLib.inputs(seekerInput,"seeker");
            }
        });

   }
    @Override protected void onPause() {
        super.onPause();
//        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
//        mView.onResume();
    }
    public long getRunningTimeMillis() {
        return System.currentTimeMillis() - startTime;
    }
}



