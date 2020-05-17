package com.android.gles3jni;
import java.io.IOException;
import java.io.InputStream;
public class MyStuff {
    static String vs1 = "1shader.vs";
    static String fs1 = "1shader.fs";
    static String vs2 = "2shader.vs";
    static String fs2 = "2shader.fs";
    static String vs3 = "3shader.vs";
    static String fs3 = "3shader.fs";

    static String inFile= "";
    public  MyStuff(ParticleSystem act){
        try {
            InputStream stream = act.getAssets().open(vs1);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            vs1 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }
        try {
            InputStream stream = act.getAssets().open(fs1);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            fs1 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }
        try {
            InputStream stream = act.getAssets().open(vs2);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            vs2 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }

        try {

            InputStream stream = act.getAssets().open(fs2);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            fs2 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }
        try {

            InputStream stream = act.getAssets().open(vs3);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            vs3 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }
        try {

            InputStream stream = act.getAssets().open(fs3);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            fs3 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }
    }
    public static String getData1(){
        return vs1;
    }
    public static String getData2(){
        return fs1;
    }
    public static String getData3(){
        return vs2;
    }
    public static String getData4(){
        return fs2;
    }
    public static String getData5(){
        return vs3;
    }
    public static String getData6(){
        return fs3;
    }

}
