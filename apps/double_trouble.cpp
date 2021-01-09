#include <iostream>
#include <vector>
#include <filesystem>
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

    int levelsUnlocked;
    if (std::filesystem::exists(PATH_TO_SAVED_GAME)) {
        std::ifstream savedGameFile(PATH_TO_SAVED_GAME);
        std::string line;
        getline(savedGameFile, line);
        levelsUnlocked = (int) std::strtol(line.c_str(), nullptr, 10);
    } else {
        std::ofstream savedGameFile(PATH_TO_SAVED_GAME);
        savedGameFile << "1\n";
        levelsUnlocked = 1;
    }

    SDL_Texture *player1AnimationSprites[2];
    player1AnimationSprites[0] = loadTexture(ren,
                                             "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Player/player_walk1.bmp");
    player1AnimationSprites[1] = loadTexture(ren,
                                             "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Player/player_walk2.bmp");
    SDL_Event e;
    Sprite player1(RIGHT, 2, Coordinates(200, 0), player1AnimationSprites, 0.25f);
    Sprite player2(RIGHT, 2, Coordinates(200, 370), player1AnimationSprites, 0.25f);
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
    Level level1(level1File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level2File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level2.txt");
    Level level2(level2File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level3File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level3.txt");
    Level level3(level3File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level4File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level4.txt");
    Level level4(level4File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level5File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level5.txt");
    Level level5(level5File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level6File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level6.txt");
    Level level6(level6File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level7File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level7.txt");
    Level level7(level7File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level8File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level8.txt");
    Level level8(level8File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level9File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level9.txt");
    Level level9(level9File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level10File("/home/mathi/workspace/advanced_c++/double_trouble/res/levels/Level10.txt");
    Level level10(level10File, wallTexture, lavaTexture, finishFlagTexture);
    Level levels[NR_OF_LEVELS] = {level1,level2,level3,level4,level5,level6,level7,level8,level9,level10};
    int currentLevel = 0;
    int maxLevel = 9;
    bool quit = false;

    // Background colour
    bool levelDone = false;
    int showLevelInfo = SDL_GetTicks();
    bool openMenu = true;
    while (!quit) {
        if (openMenu) {
            openMenu = false;
            if (showMainMenu(ren, currentLevel, levelsUnlocked) == EXIT) {
                return EXIT_SUCCESS;
            }
            showLevelInfo = SDL_GetTicks();
            player1.resetPosition(levels[currentLevel].startingPosPlayer1);
            player2.resetPosition(levels[currentLevel].startingPosPlayer2);
            continue;
        }

        SDL_SetRenderDrawColor(ren, 70, 70, 70, 0);
        
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
                        break;
                    case SDLK_ESCAPE:
                        openMenu = true;
                        break;
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

        // todo refactor this
        if (otherCollisionDetection(player1, levels[currentLevel].staticEnemies)) {
            player1.resetPosition(levels[currentLevel].startingPosPlayer1);
            player2.resetPosition(levels[currentLevel].startingPosPlayer2);
            showLevelInfo = SDL_GetTicks();
        }

        // todo refactor this
        if (otherCollisionDetection(player2, levels[currentLevel].staticEnemies)) {
            player1.resetPosition(levels[currentLevel].startingPosPlayer1);
            player2.resetPosition(levels[currentLevel].startingPosPlayer2);
            showLevelInfo = SDL_GetTicks();
        }

        if (otherCollisionDetection(player1, levels[currentLevel].finishElements)
            && otherCollisionDetection(player2, levels[currentLevel].finishElements)) {
            if (currentLevel + 1 == levelsUnlocked) {
                std::ofstream savedGameFile(PATH_TO_SAVED_GAME);
                levelsUnlocked++;
                savedGameFile << levelsUnlocked << "\n";
            }
            levelDone = true;
        }

        player1.position.x += (int) player1.velocity_x;
        player1.velocity_x = 0;

        player2.position.x += (int) player2.velocity_x;
        player2.velocity_x = 0;

        // Drawing Phase
        player1.calculateCurrentPosition();
        player2.calculateCurrentPosition();
        SDL_RenderClear(ren);
        player1.render(ren);
        player2.render(ren);
        drawLevel(ren, levels[currentLevel]);
        if (showLevelInfo + SHOW_CURRENT_LEVEL_TIME_MS > SDL_GetTicks()) {
            levels[currentLevel].RenderLevelInfo(ren);
        }
        SDL_RenderPresent(ren);
        
        if (levelDone) {
            if (currentLevel == maxLevel) {
                quit = true;
            } else {
                player1.resetPosition(levels[currentLevel].startingPosPlayer1);
                player2.resetPosition(levels[currentLevel].startingPosPlayer2);
                levelDone = false;
                currentLevel += 1;
                showLevelInfo = SDL_GetTicks();
            }
        }
    }
    
    // todo refactor this
    SDL_RenderClear(ren);
    SDL_Texture *congratsTexture = loadTexture(ren,
                                               "/home/mathi/workspace/advanced_c++/double_trouble/res/tiles/Other/congrats.bmp");
    SDL_Rect textureBox;
    SDL_QueryTexture(congratsTexture, nullptr, nullptr, &textureBox.w, &textureBox.h);
    Coordinates gameOverCoordinates(SCREEN_WIDTH / 2 - textureBox.w * 0.4f / 2,
                                    SCREEN_HEIGHT / 2 - textureBox.h * 0.4f / 2);
    renderTexture(congratsTexture, ren, gameOverCoordinates, 0.4f);
    SDL_RenderPresent(ren);
    SDL_Delay(4000);
    SDL_DestroyTexture(congratsTexture);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}
