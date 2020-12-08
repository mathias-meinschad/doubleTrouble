#include "Sprite.hpp"
#include "Constants.hpp"
#include "SdlHelpers.hpp"

Sprite::Sprite(Direction direction, int numOfSpriteAnimations, Coordinates pos, SDL_Texture **tex, float scale)
        : direction(
        direction), numOfSpriteAnimations(numOfSpriteAnimations), position(pos) {
    animationTextures = (SDL_Texture **) malloc(sizeof(SDL_Texture *) * numOfSpriteAnimations);
    for (int i = 0; i < numOfSpriteAnimations; i++) {
        animationTextures[i] = tex[i];
    }
    textureScale = scale;
    SDL_Rect playerBox;
    SDL_QueryTexture(animationTextures[0], NULL, NULL, &playerBox.w, &playerBox.h);
    width = playerBox.w * textureScale;
    height = playerBox.h * textureScale;
}

Sprite::~Sprite() {
    for (int i = 0; i < numOfSpriteAnimations; i++) {
        SDL_DestroyTexture(animationTextures[i]);
    }
    free(animationTextures);
}

void Sprite::calculateCurrentPosition() {
    if (animationLastUpdated + ANIMATION_SPEED_IN_MS < SDL_GetTicks()) {
        if (direction == LEFT || direction == RIGHT) {
            if (grounded && !sliding) {
                currentAnimationNr = (currentAnimationNr + 1) % numOfSpriteAnimations;
                currentTexture = animationTextures[currentAnimationNr];
            }
        } else {
            currentTexture = idleTexture;
        }
        if (sliding) {
            currentTexture = slideTexture;
        }
        animationLastUpdated = SDL_GetTicks();
    }
}

void Sprite::render(SDL_Renderer *ren) {
    renderTexture(currentTexture, ren, position, textureScale, direction == LEFT);
}
