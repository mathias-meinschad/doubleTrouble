#ifndef DOUBLE_TROUBLE_LEVEL_HPP
#define DOUBLE_TROUBLE_LEVEL_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include "SDL.h"
#include "LevelObject.hpp"
#include <SDL_ttf.h>
#include "Constants.hpp"
#include "SdlHelpers.hpp"

struct Level {
    Level() = default;

    Level(std::string &filePath, SDL_Texture *wallTexture, SDL_Texture *staticEnemyTexture,
          SDL_Texture *finishFlagTexture);

    ~Level();

    void RenderLevelInfo(SDL_Renderer *ren);

    std::list<LevelObjects> walls;
    std::list<LevelObjects> staticEnemies;
    std::list<LevelObjects> finishElements;
    Position startingPosPlayer1 = Position(0, 0);
    Position startingPosPlayer2 = Position(0, 0);
    Position startingPosZombie1 = Position(0, 0);
    Position startingPosZombie2 = Position(0, 0);
    std::string name;
    Uint64 showLevelInfoTime = SDL_GetTicks();
    SDL_Texture *levelInfoTexture = nullptr;
};

void drawLevel(SDL_Renderer *ren, Level &level);


#endif //DOUBLE_TROUBLE_LEVEL_HPP
