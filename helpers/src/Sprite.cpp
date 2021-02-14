#include "Sprite.hpp"

Sprite::Sprite(Direction direction, float scale, SDL_Renderer *ren, const std::string &path)
        : direction(direction) {
    animationTextures = (SDL_Texture **) malloc(sizeof(SDL_Texture *) * NR_OF_ANIMATION_SPRITES);
    animationTextures[0] = loadTexture(ren, (path + "walk1.bmp").c_str());
    animationTextures[1] = loadTexture(ren, (path + "walk2.bmp").c_str());
    textureScale = scale;
    SDL_Rect playerBox;
    SDL_QueryTexture(animationTextures[0], NULL, NULL, &playerBox.w, &playerBox.h);
    drawBox.width = playerBox.w * textureScale;
    drawBox.height = playerBox.h * textureScale;
}

Sprite::~Sprite() {
    for (int i = 0; i < NR_OF_ANIMATION_SPRITES; i++) {
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
                currentAnimationNr = (currentAnimationNr + 1) % NR_OF_ANIMATION_SPRITES;
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

Zombie::Zombie(Direction direction, float scale, SDL_Renderer *ren, const std::string &path)
        : Sprite(direction,
                 scale,
                 ren, path) {
    // Zombies are always grounded, they cannot fall of something and their direction is right from the beginning and their speed is the constant
    grounded = true;
    direction = RIGHT;
    velocity_x = ZOMBIE_VELOCITY;
}

Player::Player(Direction direction, float scale, SDL_Renderer *ren,
               const std::string &path) : Sprite(direction, scale, ren, path) {
    idleTexture = loadTexture(ren, (path + "idle.bmp").c_str());
    slideTexture = loadTexture(ren, (path + "slide.bmp").c_str());
}

Player::~Player() {
    SDL_DestroyTexture(idleTexture);
    SDL_DestroyTexture(slideTexture);
}
