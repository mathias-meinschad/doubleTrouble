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
    explicit Level(std::string &filePath, SDL_Texture *wallTexture, SDL_Texture *staticEnemyTexture);
    Level() = default;

    std::list<Wall> walls;
    std::list<StaticEnemy> staticEnemies;
};


#endif //DOUBLE_TROUBLE_LEVEL_HPP
