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

class LevelObjects {
public:
    LevelObjects(Position position, SDL_Texture *texture, float textureScale);
    virtual ~LevelObjects() {
        SDL_DestroyTexture(texture);
    }
    
    DrawBox drawBox;
    SDL_Texture *texture;
    float textureScale;
    Position position;
};

struct StaticEnemy : LevelObjects {
    StaticEnemy(Position position, SDL_Texture* texture, float textureScale)  : LevelObjects(position, texture, textureScale) {};
};

struct Wall : LevelObjects {
    Wall(Position position, SDL_Texture *texture, float textureScale) : LevelObjects(position, texture, textureScale) {};
    bool noClip = false;
};

struct Finish : LevelObjects {
    Finish(Position position, SDL_Texture *texture, float textureScale) : LevelObjects(position, texture, textureScale) {};
};

#endif //DOUBLE_TROUBLE_LEVELOBJECT_HPP
