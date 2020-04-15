#ifndef DRAW_H
#define DRAW_H
#include <vector>
#include "assetManager.h"
#include "errorChecker.h"

class Draw {
public:
    Draw();
    Draw(AssetManager* ass);
    bool first = true;
    void transform();
    void feedBack();
};

#endif //DRAW_H
