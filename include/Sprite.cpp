#include "Sprite.hpp"
#include "Constants.hpp"
#include "SdlHelpers.hpp"

Sprite::Sprite(Direction direction, int numOfSpriteAnimations, SDL_Texture **tex, float scale)
        : direction(direction), numOfSpriteAnimations(numOfSpriteAnimations) {
    animationTextures = (SDL_Texture **) malloc(sizeof(SDL_Texture *) * numOfSpriteAnimations);
    for (int i = 0; i < numOfSpriteAnimations; i++) {
        animationTextures[i] = tex[i];
    }
    textureScale = scale;
    SDL_Rect playerBox;
    SDL_QueryTexture(animationTextures[0], NULL, NULL, &playerBox.w, &playerBox.h);
    drawBox.width = playerBox.w * textureScale;
    drawBox.height = playerBox.h * textureScale;
    slideTexture = nullptr;
    idleTexture = nullptr;
}

Sprite::~Sprite() {
    for (int i = 0; i < numOfSpriteAnimations; i++) {
        SDL_DestroyTexture(animationTextures[i]);
    }
    if (slideTexture != nullptr) {
        SDL_DestroyTexture(slideTexture);
    }
    if (idleTexture != nullptr) {
        SDL_DestroyTexture(idleTexture);
    }
    free(animationTextures);
}

void Sprite::calculateCurrentAnimation() {
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

void Sprite::resetPosition(Position pos) {
    position.x = pos.x;
    position.y = pos.y;
    direction = RIGHT;
}
