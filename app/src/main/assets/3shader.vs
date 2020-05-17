#version 300 es
layout(location = 0) in vec3 pos;
uniform mat4 VMat2;
uniform mat4 PMat2;
uniform vec3 time2;
out vec3 col;
void main() {
    col = vec3(0.0f);
    gl_PointSize =  2.5;
    float PI = 3.14159265;
    vec2 P =pos.xy+time2.xy;
    float gravity= -10.0f;
    float r = length(P)*0.3f;
    if (length(r) > 0.001f ){
         gravity = 1.0-0.35f/(r*r);
    }
    if( pos.z > -1.5){
        col = vec3(1.0,0.0,0.0);
        gl_Position=PMat2*VMat2*vec4(P,gravity, 1.0f);
    }

}
//\0