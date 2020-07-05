#ifndef WORLD_H
#define WORLD_H
#include <vector>

class Grid{
public:
    int m_baseIndex;
    float w,h;
    Grid(const int * dispXY, int baseIndex);
    void setPositions(std::vector<float>& verts);
    void initVelocities(std::vector<float>& vels);
    int index_number;

    ~Grid();
};
class Circle{
public:
    int m_baseIndex;
    float w,h;
    void setPositions(std::vector<float>& verts);
    void initVelocities(std::vector<float>& vels);
    Circle(int * dispXY, int baseIndex);
    float radius;
    ~Circle();

    int index_number;
};

#endif //WORLD_H
