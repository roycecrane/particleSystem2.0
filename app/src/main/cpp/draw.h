#ifndef DRAW_H
#define DRAW_H
#include <vector>
#include "assetManager.h"
#include "errorChecker.h"

class Draw {
public:

    Draw();


    Draw(AssetManager* ass);
    void drawCalls();
    bool first = true;
    void transform();
    void draw();
    float *fb2;
    void draw2();
    float *fb;
    float* cam;
     glm::mat4 Model;
     glm::mat4 View;
     glm::mat4 Projection;

     int numPoints =0;
};

#endif //DRAW_H
