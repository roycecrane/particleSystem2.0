#version 300 es
precision mediump float;
out vec4 outColor;
in vec3 B;
void main() {
outColor = vec4(B,1.0f);
}
//\0