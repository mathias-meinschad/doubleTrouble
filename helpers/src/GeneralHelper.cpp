#include "CollisionDetection.hpp"
#include "GeneralHelper.hpp"

void renderCongrats(SDL_Renderer *ren) {
    SDL_RenderClear(ren);
    SDL_Texture *congratsTexture = loadTexture(ren,
                                               "res/tiles/Other/congrats.bmp");
    SDL_Rect textureBox;
    SDL_QueryTexture(congratsTexture, nullptr, nullptr, &textureBox.w, &textureBox.h);
    Position gameOverCoordinates(SCREEN_WIDTH / 2 - textureBox.w * 0.4f / 2,
                                 SCREEN_HEIGHT / 2 - textureBox.h * 0.4f / 2);
    renderTexture(congratsTexture, ren, gameOverCoordinates, 0.4f);
    SDL_RenderPresent(ren);
    SDL_Delay(4000);
    SDL_DestroyTexture(congratsTexture);
}

void resetPositions(const Level &level, Sprite &player1, Sprite &player2, Sprite &zombie1, Sprite &zombie2) {
    player1.resetPosition(level.startingPosPlayer1);
    player2.resetPosition(level.startingPosPlayer2);
    zombie1.resetPosition(level.startingPosZombie1);
    zombie2.resetPosition(level.startingPosZombie2);
}

int getUnlockedLevels() {
    if (std::filesystem::exists(PATH_TO_SAVED_GAME)) {
        std::ifstream savedGameFile(PATH_TO_SAVED_GAME);
        std::string line;
        getline(savedGameFile, line);
        return (int) std::strtol(line.c_str(), nullptr, 10);
    } else {
        std::ofstream savedGameFile(PATH_TO_SAVED_GAME);
        savedGameFile << "1\n";
        return 1;
    }
}

void inputPhase(Player &player1, Player &player2) {
    if (KeyboardHandler::isPressed(SDLK_a) || KeyboardHandler::isPressed(SDLK_LEFT)) {
        player1.direction = LEFT;
        player1.velocity_x -= 2;
        player2.direction = LEFT;
        player2.velocity_x -= 2;
    }
    if (KeyboardHandler::isPressed(SDLK_d) || KeyboardHandler::isPressed(SDLK_RIGHT)) {
        player1.direction = RIGHT;
        player1.velocity_x += 2;
        player2.direction = RIGHT;
        player2.velocity_x += 2;
    }
    if (KeyboardHandler::isPressed(SDLK_s) || KeyboardHandler::isPressed(SDLK_DOWN)) {
        player1.sliding = true;
        player2.sliding = true;
    }
    if (KeyboardHandler::isReleased(SDLK_s) && KeyboardHandler::isReleased(SDLK_DOWN)) {
        player1.sliding = false;
        player2.sliding = false;
    }

    if (KeyboardHandler::isReleased(SDLK_a) && KeyboardHandler::isReleased(SDLK_LEFT)
        && KeyboardHandler::isReleased(SDLK_d) && KeyboardHandler::isReleased(SDLK_RIGHT)
        && KeyboardHandler::isReleased(SDLK_s) && KeyboardHandler::isReleased(SDLK_DOWN)) {
        player1.direction = NONE;
        player2.direction = NONE;
    }

    if (!player1.grounded) {
        player1.position.y -= (int) player1.velocity_y;
        player1.velocity_y =
                player1.velocity_y + GRAVITY > MAX_VELOCITY_Y ? player1.velocity_y + GRAVITY : MAX_VELOCITY_Y;
    }

    if (!player2.grounded) {
        player2.position.y -= (int) player2.velocity_y;
        player2.velocity_y =
                player2.velocity_y + GRAVITY > MAX_VELOCITY_Y ? player2.velocity_y + GRAVITY : MAX_VELOCITY_Y;
    }
}

void positioningPhase(Player &player1, Player &player2, Zombie &zombie1, Zombie &zombie2) {
    player1.position.x += (int) player1.velocity_x;
    player1.velocity_x = 0;

    player2.position.x += (int) player2.velocity_x;
    player2.velocity_x = 0;

    zombie1.position.x += (int) zombie1.velocity_x;
    zombie2.position.x += (int) zombie2.velocity_x;
}
