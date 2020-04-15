#ifndef WORLD_H
#define WORLD_H
class World {
public:
    virtual void initMeshData() = 0;
    int index_number;
    float * position;
    float * velocity;
};
class Triangle: public World{
public:
    void initMeshData();
    Triangle();
};
class particleSystem: public World{
public:
    int numIndices;
    float shapeWidth;
    float shape_height;
    float sampleVelocity;
    float w,h;
    particleSystem(float* pos, float* vel,int sideA,int sideB,int* dispXY);
   ~particleSystem();
  void initMeshData();
};

#endif //WORLD_H
