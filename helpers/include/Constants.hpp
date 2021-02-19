#ifndef DOUBLE_TROUBLE_CONSTANTS_HPP
#define DOUBLE_TROUBLE_CONSTANTS_HPP

#include <string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int ANIMATION_SPEED_IN_MS = 250;

const int NR_MENU_ITEMS = 3;

const float GRAVITY = -1.0f;
// max velocity y is needed to not fall through small walls
const float MAX_VELOCITY_Y = -25.0f;
const float JUMP_POWER = 15.0f;
// so we cannot fly around
const int JUMP_TICKS = 700;

const float ZOMBIE_VELOCITY = 1.0f;

const int SHOW_CURRENT_LEVEL_TIME_MS = 3000;

const int NR_OF_LEVELS = 10;
const int NR_OF_ANIMATION_SPRITES = 2;

const std::string PATH_TO_SAVED_GAME = "res/levels/unlockedLevels.txt";

#endif //DOUBLE_TROUBLE_CONSTANTS_HPP
