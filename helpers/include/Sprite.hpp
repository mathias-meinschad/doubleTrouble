#ifndef DOUBLE_TROUBLE_SPRITE_HPP
#define DOUBLE_TROUBLE_SPRITE_HPP

#include "LevelObject.hpp"
#include "Constants.hpp"
#include "SdlHelpers.hpp"

enum Direction {
    NONE,
    LEFT,
    RIGHT
};

class Sprite {
public:
    Sprite(Direction direction, float scale, SDL_Renderer *ren, const std::string& path);

    ~Sprite();

    void calculateCurrentAnimation();

    void render(SDL_Renderer *ren);

    void resetPosition(Position pos);

    Direction direction;
    Position position = Position(0, 0);
    SDL_Texture *currentTexture;
    SDL_Texture **animationTextures;
    SDL_Texture *idleTexture;
    SDL_Texture *slideTexture;
    DrawBox drawBox;
    bool sliding = false;
    int currentAnimationNr = 0;
    float textureScale = 1;
    float velocity_y = 0;
    float velocity_x = 0;
    bool grounded = false;
    Uint64 animationLastUpdated = 0;
    Uint64 lastJump = 0;
};

class Player: public Sprite {
public:
    Player(Direction direction, float scale, SDL_Renderer* ren, const std::string& path);
    ~Player();
};

class Zombie : public Sprite {
public:
    Zombie(Direction direction, float scale, SDL_Renderer* ren, const std::string& path);
};


#endif //DOUBLE_TROUBLE_SPRITE_HPP
