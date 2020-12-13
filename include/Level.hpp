#ifndef DOUBLE_TROUBLE_LEVEL_HPP
#define DOUBLE_TROUBLE_LEVEL_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include "SDL.h"
#include "LevelObject.hpp"

struct Level {
    Level(std::string &filePath, SDL_Texture *wallTexture, SDL_Texture *staticEnemyTexture, SDL_Texture *finishFlagTexture);
    Level() = default;

    std::list<Wall> walls;
    std::list<LevelObjects> staticEnemies;
    std::list<LevelObjects> finishElements;
};


#endif //DOUBLE_TROUBLE_LEVEL_HPP
