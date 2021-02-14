#include "LevelObject.hpp"

LevelObjects::LevelObjects(Position position, SDL_Texture *texture, float textureScale) : texture(texture),
                                                                                          position(position),
                                                                                          textureScale(textureScale) {
    SDL_Rect textureBox;
    SDL_QueryTexture(texture, NULL, NULL, &textureBox.w, &textureBox.h);
    drawBox.width = textureBox.w * textureScale;
    drawBox.height = textureBox.h * textureScale;
}
