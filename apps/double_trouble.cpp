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
    std::cout << std::filesystem::current_path() << std::endl;
    
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
    player1AnimationSprites[0] = loadTexture(ren,"res/tiles/Player/player_walk1.bmp");
    player1AnimationSprites[1] = loadTexture(ren,"res/tiles/Player/player_walk2.bmp");
    SDL_Texture *player2AnimationSprites[2];
    player2AnimationSprites[0] = loadTexture(ren,"res/tiles/Female/female_walk1.bmp");
    player2AnimationSprites[1] = loadTexture(ren,"res/tiles/Female/female_walk2.bmp");
    SDL_Texture *zombieAnimationSprites[2];
    zombieAnimationSprites[0] = loadTexture(ren,"res/tiles/Zombie/zombie_walk1.bmp");
    zombieAnimationSprites[1] = loadTexture(ren,"res/tiles/Zombie/zombie_walk2.bmp");
    SDL_Event e;
    Sprite player1(RIGHT, 2, player1AnimationSprites, 0.25f);
    Sprite player2(RIGHT, 2, player2AnimationSprites, 0.25f);
    Sprite zombie1(RIGHT, 2, zombieAnimationSprites, 0.25f);
    Sprite zombie2(RIGHT, 2, zombieAnimationSprites, 0.25f);
    zombie1.velocity_x = ZOMBIE_VELOCITY;
    zombie2.velocity_x = ZOMBIE_VELOCITY;
    zombie1.grounded = true;
    zombie2.grounded = true;
    player1.slideTexture = loadTexture(ren,"res/tiles/Player/player_slide.bmp");
    player1.idleTexture = loadTexture(ren,"res/tiles/Player/player_idle.bmp");
    player2.slideTexture = loadTexture(ren,"res/tiles/Female/female_slide.bmp");
    player2.idleTexture = loadTexture(ren,"res/tiles/Female/female_idle.bmp");

    SDL_Texture *wallTexture = loadTexture(ren,"res/tiles/Walls/simple_wall.bmp");
    SDL_Texture *lavaTexture = loadTexture(ren,"res/tiles/Walls/simple_lava.bmp");
    SDL_Texture *finishFlagTexture = loadTexture(ren,"res/tiles/Other/finish_flag.bmp");

    std::string level1File("res/levels/Level1.txt");
    Level level1(level1File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level2File("res/levels/Level2.txt");
    Level level2(level2File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level3File("res/levels/Level3.txt");
    Level level3(level3File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level4File("res/levels/Level4.txt");
    Level level4(level4File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level5File("res/levels/Level5.txt");
    Level level5(level5File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level6File("res/levels/Level6.txt");
    Level level6(level6File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level7File("res/levels/Level7.txt");
    Level level7(level7File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level8File("res/levels/Level8.txt");
    Level level8(level8File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level9File("res/levels/Level9.txt");
    Level level9(level9File, wallTexture, lavaTexture, finishFlagTexture);
    std::string level10File("res/levels/Level10.txt");
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
            zombie1.resetPosition(levels[currentLevel].startingPosZombie1);
            zombie2.resetPosition(levels[currentLevel].startingPosZombie2);
            zombie1.direction = RIGHT;
            zombie2.direction = RIGHT;
            zombie1.velocity_x = ZOMBIE_VELOCITY;
            zombie2.velocity_x = ZOMBIE_VELOCITY;
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

        if (wallCollisionDetection(zombie1, levels[currentLevel].walls)) {
            zombie1.direction = zombie1.direction == LEFT ? RIGHT : LEFT;
            zombie1.velocity_x = zombie1.direction == LEFT ? (-ZOMBIE_VELOCITY) : ZOMBIE_VELOCITY;
        }

        if (wallCollisionDetection(zombie2, levels[currentLevel].walls)) {
            zombie2.direction = zombie2.direction == LEFT ? RIGHT : LEFT;
            zombie2.velocity_x = zombie2.direction == LEFT ? (-ZOMBIE_VELOCITY) : ZOMBIE_VELOCITY;
        }

        // todo refactor this
        if (objectCollisionDetection(player1, levels[currentLevel].staticEnemies)) {
            SDL_Delay(500);
            player1.resetPosition(levels[currentLevel].startingPosPlayer1);
            player2.resetPosition(levels[currentLevel].startingPosPlayer2);
            zombie1.resetPosition(levels[currentLevel].startingPosZombie1);
            zombie2.resetPosition(levels[currentLevel].startingPosZombie2);
            zombie1.direction = RIGHT;
            zombie2.direction = RIGHT;
            zombie1.velocity_x = ZOMBIE_VELOCITY;
            zombie2.velocity_x = ZOMBIE_VELOCITY;
            showLevelInfo = SDL_GetTicks();
        }

        // todo refactor this
        if (objectCollisionDetection(player2, levels[currentLevel].staticEnemies)) {
            SDL_Delay(500);
            player1.resetPosition(levels[currentLevel].startingPosPlayer1);
            player2.resetPosition(levels[currentLevel].startingPosPlayer2);
            zombie1.resetPosition(levels[currentLevel].startingPosZombie1);
            zombie2.resetPosition(levels[currentLevel].startingPosZombie2);
            zombie1.direction = RIGHT;
            zombie2.direction = RIGHT;
            zombie1.velocity_x = ZOMBIE_VELOCITY;
            zombie2.velocity_x = ZOMBIE_VELOCITY;
            showLevelInfo = SDL_GetTicks();
        }
        
        // todo refactor this
        if (objectCollisionDetection(player1, levels[currentLevel].finishElements)
            && objectCollisionDetection(player2, levels[currentLevel].finishElements)) {
            if (currentLevel + 1 == levelsUnlocked) {
                std::ofstream savedGameFile(PATH_TO_SAVED_GAME);
                levelsUnlocked++;
                savedGameFile << levelsUnlocked << "\n";
            }
            levelDone = true;
        }

        // todo refactor this
        if (spriteCollisionDetection(player1, zombie1)
            || spriteCollisionDetection(player1, zombie2)
            || spriteCollisionDetection(player2, zombie2)
            || spriteCollisionDetection(player2, zombie1)) {
            SDL_Delay(500);
            player1.resetPosition(levels[currentLevel].startingPosPlayer1);
            player2.resetPosition(levels[currentLevel].startingPosPlayer2);
            zombie1.resetPosition(levels[currentLevel].startingPosZombie1);
            zombie2.resetPosition(levels[currentLevel].startingPosZombie2);
            zombie1.direction = RIGHT;
            zombie2.direction = RIGHT;
            zombie1.velocity_x = ZOMBIE_VELOCITY;
            zombie2.velocity_x = ZOMBIE_VELOCITY;
            showLevelInfo = SDL_GetTicks();
        }

        player1.position.x += (int) player1.velocity_x;
        player1.velocity_x = 0;

        player2.position.x += (int) player2.velocity_x;
        player2.velocity_x = 0;
        
        zombie1.position.x += (int) zombie1.velocity_x;
        zombie2.position.x += (int) zombie2.velocity_x;

        // Drawing Phase
        player1.calculateCurrentAnimation();
        player2.calculateCurrentAnimation();
        zombie1.calculateCurrentAnimation();
        zombie2.calculateCurrentAnimation();
        SDL_RenderClear(ren);
        player1.render(ren);
        player2.render(ren);
        zombie1.render(ren);
        zombie2.render(ren);
        drawLevel(ren, levels[currentLevel]);
        if (showLevelInfo + SHOW_CURRENT_LEVEL_TIME_MS > SDL_GetTicks()) {
            levels[currentLevel].RenderLevelInfo(ren);
        }
        SDL_RenderPresent(ren);
        
        if (levelDone) {
            if (currentLevel == maxLevel) {
                quit = true;
            } else {
                currentLevel += 1;
                // TODO: refactor
                player1.resetPosition(levels[currentLevel].startingPosPlayer1);
                player2.resetPosition(levels[currentLevel].startingPosPlayer2);
                zombie1.resetPosition(levels[currentLevel].startingPosZombie1);
                zombie2.resetPosition(levels[currentLevel].startingPosZombie2);
                zombie1.direction = RIGHT;
                zombie2.direction = RIGHT;
                zombie1.velocity_x = ZOMBIE_VELOCITY;
                zombie2.velocity_x = ZOMBIE_VELOCITY;
                levelDone = false;
                showLevelInfo = SDL_GetTicks();
            }
        }
    }
    
    // todo refactor this
    SDL_RenderClear(ren);
    SDL_Texture *congratsTexture = loadTexture(ren,
                                               "res/tiles/Other/congrats.bmp");
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
