#ifndef DOUBLE_TROUBLE_MENU_HPP
#define DOUBLE_TROUBLE_MENU_HPP

#include "SDL.h"
#include "SDL_ttf.h"
#include "Constants.hpp"
#include "SdlHelpers.hpp"

enum MenuEntries {
    NEW_GAME,
    SELECT_LEVEL,
    PREVIOUS_MENU,
    EXIT,
};

MenuEntries showMainMenu(SDL_Renderer *ren, int &currentLevel, int &levelsUnlocked);

#endif //DOUBLE_TROUBLE_MENU_HPP
