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

struct Level {
    Level(std::string &filePath, SDL_Texture *wallTexture, SDL_Texture *staticEnemyTexture, SDL_Texture *finishFlagTexture);
    void RenderLevelInfo(SDL_Renderer* ren);

    std::list<Wall> walls;
    std::list<LevelObjects> staticEnemies;
    std::list<LevelObjects> finishElements;
    // defaulted
    Position startingPosPlayer1 = Position(0, 0);
    Position startingPosPlayer2 = Position(0, 0);
    Position startingPosZombie1 = Position(0, 0);
    Position startingPosZombie2 = Position(0, 0);
    std::string name;
    
};


#endif //DOUBLE_TROUBLE_LEVEL_HPP
