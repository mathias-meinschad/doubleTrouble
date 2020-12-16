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
    Level() = default;
    void RenderLevelInfo(SDL_Renderer* ren);

    std::list<Wall> walls;
    std::list<LevelObjects> staticEnemies;
    std::list<LevelObjects> finishElements;
    std::string name;
};


#endif //DOUBLE_TROUBLE_LEVEL_HPP
