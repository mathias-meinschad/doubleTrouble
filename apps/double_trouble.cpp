#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "../include/KeyboardHandler.hpp"
#include "../include/SdlHelpers.hpp"
#include "../include/Sprite.hpp"
#include "../include/CollisionDetection.h"
#include "../include/Menu.h"

int main() {
    SDL_Window *win;
    SDL_Renderer *ren;
    if (!init(win, ren)) {
        return EXIT_FAILURE;
    }

    if (TTF_Init() < 0) {
        std::cout << TTF_GetError() << "\n";
    }


    SDL_Texture *player1AnmiationSprites[2];
    player1AnmiationSprites[0] = loadTexture(ren,
                                             "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Player/player_walk1.bmp");
    player1AnmiationSprites[1] = loadTexture(ren,
                                             "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Player/player_walk2.bmp");
    SDL_Event e;
    Sprite player1(RIGHT, 2, Coordinates(200, 0), player1AnmiationSprites, 0.25f);
    Sprite player2(RIGHT, 2, Coordinates(200, 370), player1AnmiationSprites, 0.25f);
    player1.slideTexture = loadTexture(ren,
                                       "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Player/player_slide.bmp");
    player1.idleTexture = loadTexture(ren,
                                      "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Player/player_idle.bmp");
    player2.slideTexture = loadTexture(ren,
                                       "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Player/player_slide.bmp");
    player2.idleTexture = loadTexture(ren,
                                      "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Player/player_idle.bmp");

    SDL_Texture *wallTexture = loadTexture(ren,
                                           "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Walls/simple_wall.bmp");

    SDL_Texture *lavaTexture = loadTexture(ren,
                                           "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Walls/simple_lava.bmp");

    SDL_Texture *finishFlagTexture = loadTexture(ren,
                                                 "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Other/finish_flag.bmp");

    std::string level1File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level1.txt");
    Level level1(level1File, wallTexture, lavaTexture, finishFlagTexture);;
    std::string level2File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level2.txt");
    Level level2(level2File, wallTexture, lavaTexture, finishFlagTexture);;
    Level levels[2];
    levels[0] = level1;
    levels[1] = level2;
    int currentLevel = 0;
    int maxLevel = 1;
    bool quit = false;
    
    MenuEntries selectedEntry = showmenu(ren);
    if (selectedEntry == NEW_GAME) {
        currentLevel = 0;
    }
    if (selectedEntry == EXIT) {
        return EXIT_SUCCESS;
    }

    // Background colour
    SDL_SetRenderDrawColor(ren, 70, 70, 70, 0);
    bool levelDone = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            KeyboardHandler::handleKeyboardEvent(e);
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_w:
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
                }
            }
        }

        // input handling/positioning phase
        if (KeyboardHandler::isPressed(SDLK_a)) {
            player1.direction = LEFT;
            player1.velocity_x -= 2;
            player2.direction = LEFT;
            player2.velocity_x -= 2;
        }
        if (KeyboardHandler::isPressed(SDLK_d)) {
            player1.direction = RIGHT;
            player1.velocity_x += 2;
            player2.direction = RIGHT;
            player2.velocity_x += 2;
        }
        if (KeyboardHandler::isPressed(SDLK_s)) {
            player1.sliding = true;
            player2.sliding = true;
        }
        if (KeyboardHandler::isReleased(SDLK_s)) {
            player1.sliding = false;
            player2.sliding = false;
        }

        if (KeyboardHandler::isReleased(SDLK_a) && KeyboardHandler::isReleased(SDLK_d) &&
            KeyboardHandler::isReleased(SDLK_s)) {
            player1.direction = NONE;
            player2.direction = NONE;
        }

        if (KeyboardHandler::isPressed(SDLK_ESCAPE)) {
            quit = true;
        }

        if (!player1.grounded) {
            player1.position.y -= (int) player1.velocity_y;
            player1.velocity_y += GRAVITY;
            if (player1.position.y > SCREEN_HEIGHT - 20) {
                player1.position.y = SCREEN_HEIGHT - 20;
                player1.grounded = true;
                player1.velocity_y = 0;
            }
        }

        if (!player2.grounded) {
            player2.position.y -= (int) player2.velocity_y;
            player2.velocity_y += GRAVITY;
            if (player2.position.y > SCREEN_HEIGHT - 20) {
                player2.position.y = SCREEN_HEIGHT - 20;
                player2.grounded = true;
                player2.velocity_y = 0;
            }
        }

        if (!wallCollisionDetection(player1, levels[currentLevel].walls)) {
            player1.grounded = false;
        }

        if (!wallCollisionDetection(player2, levels[currentLevel].walls)) {
            player2.grounded = false;
        }

        if (otherCollisionDetection(player1, levels[currentLevel].staticEnemies)) {
            quit = true;
        }

        if (otherCollisionDetection(player2, levels[currentLevel].staticEnemies)) {
            quit = true;
        }

        if (otherCollisionDetection(player1, levels[currentLevel].finishElements)
            && otherCollisionDetection(player2, levels[currentLevel].finishElements)) {
            levelDone = true;
        }

        player1.position.x += player1.velocity_x;
        player1.velocity_x = 0;

        player2.position.x += player2.velocity_x;
        player2.velocity_x = 0;

        // Drawing Phase
        player1.calculateCurrentPosition();
        player2.calculateCurrentPosition();
        SDL_RenderClear(ren);
        player1.render(ren);
        player2.render(ren);
        drawLevel(ren, levels[currentLevel]);
        SDL_RenderPresent(ren);
        
        if (levelDone) {
            if (currentLevel == maxLevel) {
                quit = true;
            } else {
                player1.resetPosition(Coordinates(200,0));
                player2.resetPosition(Coordinates(200,370));
                levelDone = false;
                currentLevel += 1;    
            }
        }
    }
    
    // todo refactor this
    if (levelDone) {
        SDL_RenderClear(ren);
        SDL_Texture *congratsTexture = loadTexture(ren, "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Other/congrats.bmp");
        SDL_Rect textureBox;
        SDL_QueryTexture(congratsTexture, NULL, NULL, &textureBox.w, &textureBox.h);
        Coordinates gameOverCoordinates(SCREEN_WIDTH / 2 - textureBox.w * 0.4f / 2 ,SCREEN_HEIGHT / 2 - textureBox.h * 0.4f / 2);
        renderTexture(congratsTexture, ren, gameOverCoordinates, 0.4f);
        SDL_RenderPresent(ren);
        SDL_Delay(5000);
        SDL_DestroyTexture(congratsTexture);
    } else {
        SDL_Texture *gameOverTexture = loadTexture(ren, "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Other/game_over.bmp");
        SDL_Rect textureBox;
        SDL_QueryTexture(gameOverTexture, NULL, NULL, &textureBox.w, &textureBox.h);
        Coordinates gameOverCoordinates(SCREEN_WIDTH / 2 - textureBox.w / 2,SCREEN_HEIGHT / 2 - textureBox.h / 2);
        renderTexture(gameOverTexture, ren, gameOverCoordinates, 1.0f);
        SDL_RenderPresent(ren);
        SDL_Delay(1000);
        SDL_DestroyTexture(gameOverTexture);
    }
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}
