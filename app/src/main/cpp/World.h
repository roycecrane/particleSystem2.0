#ifndef WORLD_H
#define WORLD_H
#include <vector>
class World {
public:
    virtual float* getPositions() = 0;
    virtual float* initVelocities() = 0;
    virtual int setPositions() = 0;
    int index_number;
    float sampleVelocity;


};
class Triangle: public World{
public:
    int index_number;
    float sampleVelocity;
    float* m_vertcies;
    float* m_velocities;

    float* getPositions();
    float* initVelocities();
    Triangle(float* verts);


};
class particleSystem: public World{
public:
    float radius;
    float sampleVelocity;
     int index_number;
        int circleIndexNum;

    float * m_vertcies;
    float *  m_velocities;
    float w,h;
    void circle();

    static std::vector<float> vertVec;
    static std::vector<float> velVec;
    void mesh();
    particleSystem(float * verts,float* velocities, int* dispXY);
    float * getPositions();
    float* initVelocities();
    int setPositions();
    ~particleSystem();


};


#endif //WORLD_H
