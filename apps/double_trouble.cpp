#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "KeyboardHandler.hpp"
#include "SdlHelpers.hpp"
#include "Sprite.hpp"
#include "CollisionDetection.hpp"
#include "Menu.hpp"
#include "GeneralHelper.hpp"

int main() {
    SDL_Window *win;
    SDL_Renderer *ren;
    if (!init(win, ren)) {
        return EXIT_FAILURE;
    }

    if (TTF_Init() < 0) {
        std::cout << TTF_GetError() << "\n";
    }

    // creating players and zombies
    Player player1(RIGHT, 0.25f, ren, "res/tiles/Player/");
    Player player2(RIGHT, 0.25f, ren, "res/tiles/Female/");
    Zombie zombie1(RIGHT, 0.25f, ren, "res/tiles/Zombie/");
    Zombie zombie2(RIGHT, 0.25f, ren, "res/tiles/Zombie/");

    // creating textures for levels
    SDL_Texture *wallTexture = loadTexture(ren, "res/tiles/Walls/simple_wall.bmp");
    SDL_Texture *staticEnemyTexture = loadTexture(ren, "res/tiles/Walls/simple_lava.bmp");
    SDL_Texture *finishFlagTexture = loadTexture(ren, "res/tiles/Other/finish_flag.bmp");

    // creating levels
    Level levels[NR_OF_LEVELS];
    for (int i = 0; i < NR_OF_LEVELS; i++) {
        auto levelPath = "res/levels/Level" + std::to_string(i + 1) + ".txt";
        levels[i] = Level(levelPath, wallTexture, staticEnemyTexture, finishFlagTexture);;
    }

    // important variables for level advancement + level info + menu
    int levelsUnlocked = getUnlockedLevels();
    int currentLevel = 0;
    int maxLevel = 9;
    bool quit = false;
    bool levelDone;
    levels[currentLevel].showLevelInfoTime = SDL_GetTicks();
    bool openMenu = true;
    SDL_Event e;
    while (!quit) {
        if (openMenu) {
            openMenu = false;
            if (showMainMenu(ren, currentLevel, levelsUnlocked) == EXIT) {
                return EXIT_SUCCESS;
            }
            levels[currentLevel].showLevelInfoTime = SDL_GetTicks();
            resetPositions(levels[currentLevel], player1, player2, zombie1, zombie2);
            continue;
        }

        SDL_SetRenderDrawColor(ren, 70, 70, 70, 0);

        while (SDL_PollEvent(&e)) {
            KeyboardHandler::handleKeyboardEvent(e);
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                    case SDLK_UP:
                    case SDLK_SPACE:
                        if (player1.lastJump + JUMP_TICKS < SDL_GetTicks()) {
                            player1.grounded = false;
                            player1.velocity_y += JUMP_POWER;
                            player1.lastJump = SDL_GetTicks();
                        }
                        if (player2.lastJump + JUMP_TICKS < SDL_GetTicks()) {
                            player2.grounded = false;
                            player2.velocity_y += JUMP_POWER;
                            player2.lastJump = SDL_GetTicks();
                        }
                        break;
                    case SDLK_ESCAPE:
                        openMenu = true;
                        break;
                }
            }
        }

        // Animation calculation
        player1.calculateCurrentAnimation();
        player2.calculateCurrentAnimation();
        zombie1.calculateCurrentAnimation();
        zombie2.calculateCurrentAnimation();

        inputPhase(player1, player2);

        // collision Phase
        wallCollisionDetection(levels[currentLevel], player1, player2, zombie1, zombie2);
        levelDone = objectCollisionDetection(levels[currentLevel], player1, player2, zombie1, zombie2);

        positioningPhase(player1, player2, zombie1, zombie2);

        // Drawing Phase
        SDL_RenderClear(ren);
        player1.render(ren);
        player2.render(ren);
        zombie1.render(ren);
        zombie2.render(ren);
        drawLevel(ren, levels[currentLevel]);
        SDL_RenderPresent(ren);

        // Check if level done
        if (levelDone) {
            if (currentLevel == maxLevel) {
                quit = true;
            } else {
                if (currentLevel + 1 == levelsUnlocked) {
                    std::ofstream savedGameFile(PATH_TO_SAVED_GAME);
                    levelsUnlocked++;
                    savedGameFile << levelsUnlocked << "\n";
                }
                currentLevel += 1;
                resetPositions(levels[currentLevel], player1, player2, zombie1, zombie2);
                levelDone = false;
                levels[currentLevel].showLevelInfoTime = SDL_GetTicks();
            }
        }
    }

    renderCongrats(ren);

    // Cleanup
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(staticEnemyTexture);
    SDL_DestroyTexture(finishFlagTexture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
