#ifndef DOUBLE_TROUBLE_MENU_H
#define DOUBLE_TROUBLE_MENU_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "Constants.hpp"

enum MenuEntries {
    NEW_GAME = 0,
    SELECT_LEVEL = 1,
    EXIT = 2,
};

const int NR_MENU_ITEMS = 3;

MenuEntries showmenu(SDL_Renderer* ren);

#endif //DOUBLE_TROUBLE_MENU_H
