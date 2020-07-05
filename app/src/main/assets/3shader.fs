#version 300 es
precision mediump float;
out vec4 outColor;
in vec3 col;
void main() {
    if(length(col) > 0.0f) outColor = vec4(col.xyz,1.0f);
}
//\0