#include <math.h>
#include "vector"
#include "World.h"
#include "errorChecker.h"


Grid::Grid(const int * dispXY, int baseIndex){
    m_baseIndex=baseIndex;
    index_number = 0;
    w = (float)dispXY[0];
    h= (float)dispXY[1];

}

void Grid::setPositions(std::vector<float>& verts) {
    float xSide = 5000;
    float ySide = 50;
    float xStep =  -5.1f/((float)xSide);
    float yStep =  -5.1f/((float)ySide);
    float X =  2.0f;
    float  Y=  2.0f;
    float x = X;
    float y;
    for (int i = m_baseIndex; i < xSide ; i += 1) {
        y = Y;
        for (int j = 0; j <ySide ; j += 1) {
            verts.push_back(x);
            verts.push_back(y);
            verts.push_back(-1.0f);
            y += yStep;
            index_number+=1;
        }
        x += xStep;
    }
    y = X;
    for (int i = m_baseIndex; i < (xSide  ); i += 1) {
        x = Y;
        for (int j = 0; j <ySide; j += 1) {
            verts.push_back(x);
            verts.push_back(y);
            verts.push_back(-1.0f);
            x += yStep;

            index_number +=1;
        }
        y += xStep;
    }
}
void Grid::initVelocities(std::vector<float>& vels) {
    for (int i = 0; i < index_number ; i += 3) {
        vels.push_back(VELOCITY);
        vels.push_back(0.0f);
        vels.push_back(VELOCITY);
    }
}
Grid::~Grid() {

}
Circle::Circle(int * dispXY, int baseIndex){
    w = (float)dispXY[0];
    index_number = baseIndex;
    m_baseIndex = baseIndex;
    h= (float)dispXY[1];
}

void Circle::initVelocities(std::vector<float>& verts) {
    for (int i = 0; i < index_number-m_baseIndex ; i += 3) {
      verts.push_back(VELOCITY);
        verts.push_back(0.0f);
        verts.push_back(VELOCITY);
    }
}
void Circle::setPositions(std::vector<float>& verts) {
    float numCirlce = 300;
    float perCircle = 100;
    float pi = 3.14159265f;
    float thetaStep = 2.0f * pi/perCircle;
    float rStep = 0.02005f;
    float r = 0.0f;
    float theta;
    for (int i = 0; i < numCirlce ; i += 1) {
        theta = 0.0f;
        for (int j = 0; j <perCircle ; j += 1) {
            verts.push_back(cos(theta)*r);
            verts.push_back(sin(theta)*r);
            verts.push_back(-2.0f);
            theta += thetaStep;
            index_number+=1;
        }
        r += rStep;
    }
    radius = r;
}

Circle::~Circle() {

}




