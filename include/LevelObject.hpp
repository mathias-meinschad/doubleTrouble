#ifndef DOUBLE_TROUBLE_LEVELOBJECT_HPP
#define DOUBLE_TROUBLE_LEVELOBJECT_HPP

#include <iostream>
#include "SDL.h"

struct Coordinates {
    Coordinates(int x, int y) : x(x), y(y) {};
    int x;
    int y;
};

class LevelObjects {
public:
    LevelObjects(Coordinates position, SDL_Texture *texture, float textureScale);
    virtual ~LevelObjects() {
        SDL_DestroyTexture(texture);
    }
    
    int width;
    int height;
    SDL_Texture *texture;
    float textureScale;
    Coordinates position;
};

struct StaticEnemy : LevelObjects {
    StaticEnemy(Coordinates position, SDL_Texture* texture, float textureScale)  : LevelObjects(position, texture, textureScale) {};
};

struct Wall : LevelObjects {
    Wall(Coordinates position, SDL_Texture *texture, float textureScale) : LevelObjects(position, texture, textureScale) {};
    bool noClip = false;
};

struct Finish : LevelObjects {
    Finish(Coordinates position, SDL_Texture *texture, float textureScale) : LevelObjects(position, texture, textureScale) {};
};

#endif //DOUBLE_TROUBLE_LEVELOBJECT_HPP
