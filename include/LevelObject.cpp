#include "LevelObject.hpp"

LevelObjects::LevelObjects(Coordinates position, SDL_Texture *texture, float textureScale) : texture(texture), position(position), textureScale(textureScale) {
    SDL_Rect textureBox;
    SDL_QueryTexture(texture, NULL, NULL, &textureBox.w, &textureBox.h);
    width = textureBox.w * textureScale;
    height = textureBox.h * textureScale;
}