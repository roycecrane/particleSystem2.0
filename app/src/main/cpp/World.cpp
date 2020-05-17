#include <math.h>
#include "vector"
#include "World.h"
#include "errorChecker.h"
std::vector<float> particleSystem:: vertVec;
std::vector<float> particleSystem::velVec;

particleSystem::particleSystem(float* verts,float* velocities, int *dispXY){
    w = (float)dispXY[0];
    m_vertcies = verts;
    index_number =0;
    m_velocities = velocities;
    h= (float)dispXY[1];
    sampleVelocity = VELOCITY;
    circle();
    circleIndexNum = index_number;
    mesh();

}
float* particleSystem::getPositions() {
    return  &vertVec[0];
}

float* particleSystem::initVelocities() {
    for (int i = 0; i < index_number ; i += 3) {
        velVec.push_back(VELOCITY);
        vertVec.push_back(0.0f);
        velVec.push_back(VELOCITY);
    }
    return  &velVec[0];
}

void particleSystem::circle() {
    float numCirlce = 10;
    float perCircle = 150;
    float pi = 3.14159265f;
    float thetaStep = 2.0f * pi/perCircle;
    float rStep = 0.07005f;



    float r = 0.0f;
    float theta=0.0f;
    for (int i = 0; i < numCirlce ; i += 1) {
        theta = 0.0f;
        for (int j = 0; j <perCircle ; j += 1) {
            vertVec.push_back(cos(theta)*r);
            vertVec.push_back(sin(theta)*r);
            vertVec.push_back(-2.0f);
            theta += thetaStep;
            index_number++;
        }
        r += rStep;

    }
    radius = r;
}
void particleSystem::mesh() {


    float xSide = 5000;
    float ySide = 50;
    float xStep =  -19.1f/((float)xSide);
    float yStep =  -19.1f/((float)ySide);
    float X =  10.0f;
    float  Y=  10.0f;
    float pi = 3.14159265f;
    float x = X;
    float y;
    for (int i = 0; i < xSide ; i += 1) {
        y = Y;
        for (int j = 0; j <ySide ; j += 1) {
            vertVec.push_back(x);
            vertVec.push_back(y);
            vertVec.push_back(-1.0f);
            y += yStep;
            index_number++;
        }
        x += xStep;
    }
    y = X;
    for (int i = 0; i < (xSide  ); i += 1) {
        x = Y;
        for (int j = 0; j <ySide; j += 1) {
            vertVec.push_back(x);
            vertVec.push_back(y);
            vertVec.push_back(-1.0f);
            x += yStep;
            index_number ++;
        }
        y += xStep;
    }
}

int particleSystem::setPositions() {


    __android_log_print(ANDROID_LOG_ERROR, "indexNumber", "%i",index_number);
    return index_number;
}
particleSystem::~particleSystem() {

}
Triangle::Triangle(float* verts) {
    m_vertcies = verts;
    index_number = 9;
     sampleVelocity = 0.0;


}
float* Triangle::initVelocities() {
    m_velocities = new float[1]{0.0f};

    return m_velocities;
}
float* Triangle::getPositions() {

    float triangle[] ={-0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f};
    for (int i = 0; i <3 ; ++i) {
        for (int j = 0; j <3 ; ++j) {
        m_vertcies[i]=0.0f;
        }
    }
    return m_vertcies;
}



