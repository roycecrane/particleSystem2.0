#version 300 es
layout(location = 0) in vec3 pos2;
uniform mat4 pMAT2;
uniform mat4 vMAT2;
uniform mat4 mMAT2;
out vec3 col;
float PI = 3.14159265;
void main() {
    col = vec3(0.0f);
    gl_PointSize =  6.5;
    vec2 P =pos2.xy;
    float gravity= -1.0f;
    float r = 3.5*length(pos2.xy);
    float zz =1.0f/(r*r);
    col = vec3(length(pos2.x),length(pos2.y),0.0);


    gl_Position=pMAT2*vMAT2* vec4(pos2.xy , 1.0-zz, 1.0f);
}
//\0