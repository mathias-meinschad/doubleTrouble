#ifndef DOUBLE_TROUBLE_SDLHELPERS_HPP
#define DOUBLE_TROUBLE_SDLHELPERS_HPP

#include "SDL.h"
#include "LevelObject.hpp"
#include "Level.hpp"
#include "Constants.hpp"

bool init(SDL_Window *&win, SDL_Renderer *&ren);

void logSDLError(std::ostream &os, const std::string &msg);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, Position &position, float scale, bool flip = false);

SDL_Texture *loadTexture(SDL_Renderer *ren, const char *filePath);

void drawLevel(SDL_Renderer *ren, Level &level, Uint64 showLevelInfoTime);

#endif //DOUBLE_TROUBLE_SDLHELPERS_HPP
