#ifndef DOUBLE_TROUBLE_SPRITE_HPP
#define DOUBLE_TROUBLE_SPRITE_HPP

#include "LevelObject.hpp"

enum Direction {
    NONE,
    LEFT,
    RIGHT
};

class Sprite {
public:
    Sprite(Direction direction, int numOfSpriteAnimations, SDL_Texture **tex, float scale = 1);
    ~Sprite();
    void calculateCurrentAnimation();
    void render(SDL_Renderer *ren);
    void resetPosition(Coordinates pos);

    Direction direction;
    int numOfSpriteAnimations;
    Coordinates position = Coordinates(0,0);
    SDL_Texture *currentTexture;
    SDL_Texture **animationTextures;
    SDL_Texture *idleTexture;
    SDL_Texture *slideTexture;
    int height;
    int width;
    bool sliding = false;
    int currentAnimationNr = 0;
    float textureScale = 1;
    float velocity_y = 0;
    float velocity_x = 0;
    bool grounded = false;
    Uint64 animationLastUpdated = 0;
    Uint64 lastJump = 0;
};


#endif //DOUBLE_TROUBLE_SPRITE_HPP
