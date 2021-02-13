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

void resetPositions(const Level& level, Sprite& player1, Sprite& player2, Sprite& zombie1, Sprite& zombie2) {
    player1.resetPosition(level.startingPosPlayer1);
    player2.resetPosition(level.startingPosPlayer2);
    zombie1.resetPosition(level.startingPosZombie1);
    zombie2.resetPosition(level.startingPosZombie2);
}