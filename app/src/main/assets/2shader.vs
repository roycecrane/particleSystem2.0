#version 300 es
layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec3 vel_in;
layout(location = 2) in vec3 FBDAT_in;
layout(location = 3) in vec3 initPos_in;
layout(location = 4) in vec4 camera_in;
uniform mat4 pMAT;
uniform mat4 vMAT;
uniform mat4 mMAT;
//uniform vec4 cam;

out vec3 B;
float PI = 3.14159265;
//uniform mat4 VMat;
//uniform mat4 PMat;
    void main() {
       B = FBDAT_in;
        float size = 10.5f;
        gl_PointSize =  size;
        vec3 pos = pos_in;
        vec3 vN = normalize(vel_in);
        mat4 m= mMAT;

        if(vel_in.z==3.0f){
            B= vec3(0.0,1.0,0.0);
            gl_PointSize = 16.0f;
        }

        gl_Position=pMAT*vMAT*m* vec4(pos.xy, 0.5, 1.0f);
    }
//\0
