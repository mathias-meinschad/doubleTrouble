#ifndef DOUBLE_TROUBLE_MENU_H
#define DOUBLE_TROUBLE_MENU_H

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

const int NR_MENU_ITEMS = 3;

MenuEntries showMainMenu(SDL_Renderer* ren, int &currentLevel, int &levelsUnlocked);

#endif //DOUBLE_TROUBLE_MENU_H
