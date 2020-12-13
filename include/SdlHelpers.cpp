#include "SdlHelpers.hpp"

bool init(SDL_Window *&win, SDL_Renderer *&ren) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cout, "SDL_Init");
        return false;
    }

    win = SDL_CreateWindow("Double Trouble", 100, 100, SCREEN_WIDTH,
                           SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        logSDLError(std::cout, "CreateRenderer");
        SDL_DestroyWindow(win);
        SDL_Quit();
        return false;
    }

    return true;
}

void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, Coordinates &position, float scale, bool flip) {
    SDL_Rect dst;
    dst.x = position.x;
    dst.y = position.y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    dst.w = dst.w * scale;
    dst.h = dst.h * scale;
    if (flip) {
        SDL_RenderCopyEx(ren, tex, NULL, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopy(ren, tex, NULL, &dst);
    }
}

SDL_Texture *loadTexture(SDL_Renderer *ren, const char *filePath) {
    SDL_Surface *surface = SDL_LoadBMP(filePath);
    auto tex = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    return tex;
}

// TODO make method in level class for this
void drawLevel(SDL_Renderer *ren, Level &level) {
    for (auto &wall : level.walls) {
        renderTexture(wall.texture, ren, wall.position, wall.textureScale);
    }
    for (auto &staticEnemy : level.staticEnemies) {
        renderTexture(staticEnemy.texture, ren, staticEnemy.position, staticEnemy.textureScale);
    }
    for (auto &finishElement : level.finishElements) {
        renderTexture(finishElement.texture, ren, finishElement.position, finishElement.textureScale);
    }
}