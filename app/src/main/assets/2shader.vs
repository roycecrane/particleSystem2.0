#version 300 es
layout(location = 0) in vec3 pos_in;
layout(location = 1) in vec3 vel_in;
layout(location = 2) in vec3 FBDAT_in;
layout(location = 3) in vec3 initPos_in;
out vec3 B;

uniform mat4 VMat;
uniform mat4 PMat;
    void main() {
       B = FBDAT_in;
        float size = 7.5f;
        gl_PointSize =  size;
        vec3 pos = pos_in;
        if (pos_in.z > -3.5 &&  -1.5 > pos_in.z ){
             pos = vec3(pos.xy+initPos_in.xy,0.0);
            B = vec3(0.0, 0.6,1.0);
        }
        gl_Position= PMat*VMat*vec4(pos.xy, 2.5f, 1.0f);
    }
//\0
