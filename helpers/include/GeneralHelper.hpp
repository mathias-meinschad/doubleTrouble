#ifndef DOUBLE_TROUBLE_GENERALHELPER_HPP
#define DOUBLE_TROUBLE_GENERALHELPER_HPP

#include <SDL.h>
#include "Constants.hpp"
#include "SdlHelpers.hpp"
#include "Sprite.hpp"
#include <filesystem>
#include "KeyboardHandler.hpp"

void renderCongrats(SDL_Renderer *ren);

void resetPositions(const Level& level, Sprite& player1, Sprite& player2, Sprite& zombie1, Sprite& zombie2);

int getUnlockedLevels();

void inputPhase(Player& player1, Player& player2);

void positioningPhase(Player& player1, Player& player2, Zombie& zombie1, Zombie& zombie2);

#endif //DOUBLE_TROUBLE_GENERALHELPER_HPP
