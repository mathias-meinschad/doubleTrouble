#ifndef DOUBLE_TROUBLE_LEVELOBJECT_HPP
#define DOUBLE_TROUBLE_LEVELOBJECT_HPP

#include <iostream>
#include "SDL.h"

struct DrawBox {
    int width;
    int height;
};

struct Position {
    Position(int x, int y) : x(x), y(y) {};
    int x;
    int y;
};

struct LevelObjects {
    LevelObjects(Position position, SDL_Texture *texture, float textureScale);
    
    DrawBox drawBox;
    SDL_Texture *texture;
    float textureScale;
    Position position;
};
#endif //DOUBLE_TROUBLE_LEVELOBJECT_HPP
