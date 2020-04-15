#include <math.h>
#include "World.h"
#include "errorChecker.h"
particleSystem::particleSystem(float* pos, float* vel,int sideA,int sideB,int *dispXY) {
    index_number = sideA*sideB;
    w = (float)dispXY[0];
    h= (float)dispXY[1];
    shape_height = sideA;
    shapeWidth = sideB;
    position = pos;
    velocity = vel;
}
void particleSystem::initMeshData() {

    float xStep = 1.0f/shapeWidth;
    float yStep = 5.0f/shape_height;
    float x = (-0.25f);
    for (int i = 0; i < index_number - shape_height; i += shape_height) {
        float y = (1.0f);
        for (int j = 0; j < shape_height; j += 3) {
            position[i + j] = x;
            position[i + j + 1] =-y;
            position[i + j + 2] = -1.0f;
            y += yStep;
        }
        x += xStep*1.0f;
    }
    sampleVelocity = -1.0f*(float)5000000000000.0;
    for (int i = 0; i < index_number - 3; i += 3) {
//        velocity[i] = 1.0f*sampleVelocity*sin(position[i]);
//        velocity[i+1] = 1.0f*sampleVelocity*cos(position[i]);

        velocity[i+1] =-sampleVelocity;
    }
}
Triangle::Triangle() {
    index_number = 9;
}
void Triangle::initMeshData() {
    position = new float[9];
    velocity = new float[9]{0};
    float triangle[] ={-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    for (int i = 0; i <9 ; ++i) {
        position[i] = triangle[i];
    }
}
particleSystem::~particleSystem() {
}


