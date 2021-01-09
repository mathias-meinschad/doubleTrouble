#include "Level.hpp"

Level::Level(std::string &filePath, SDL_Texture *wallTexture, SDL_Texture *staticEnemyTexture, SDL_Texture *finishFlagTexture) {
    std::ifstream inputFile(filePath);
    if (!inputFile) {
        // TODO remove this
        std::cout << "Failed to load Level1" << "\n";
    }
    std::string line;
    getline(inputFile, line);
    name = line;
    int x, y;
    float scale;
    getline(inputFile, line);
    while (getline(inputFile, line)) {
        if (line.empty()) {
            break;
        }
        if (3 != std::sscanf(line.c_str(),"%d,%d,%f", &x, &y, &scale)) {
            std::cout << "Check level file \n";
        }
        walls.emplace_back(Coordinates(x,y), wallTexture, scale);
    }

    getline(inputFile, line);
    while (getline(inputFile, line)) {
        if (line.empty()) {
            break;
        }
        
        if (3 != std::sscanf(line.c_str(),"%d,%d,%f", &x, &y, &scale)) {
            std::cout << "Check level file \n";
        }
        staticEnemies.emplace_back(Coordinates(x, y), staticEnemyTexture, scale);
    }

    getline(inputFile, line);
    while (getline(inputFile, line)) {
        if (line.empty()) {
            break;
        }
        
        if (3 != std::sscanf(line.c_str(),"%d,%d,%f", &x, &y, &scale)) {
            std::cout << "Check level file \n";
        }
        finishElements.emplace_back(Coordinates(x, y), finishFlagTexture, scale);
    }

    getline(inputFile, line);
    getline(inputFile, line);
    if (2 != std::sscanf(line.c_str(),"%d,%d", &x, &y)) {
        std::cout << "Check level file \n";
    }
    startingPosPlayer1 = Coordinates(x, y);
    getline(inputFile, line);
    if (2 != std::sscanf(line.c_str(),"%d,%d", &x, &y)) {
        std::cout << "Check level file \n";
    }
    startingPosPlayer2 = Coordinates(x, y);
}

void Level::RenderLevelInfo(SDL_Renderer* ren) {
    TTF_Font* timesNewRoman = TTF_OpenFont("/home/mathi/workspace/advanced_c++/double_trouble/res/fonts/times_new_roman.ttf", 50);
    if (!timesNewRoman) {
        std::cout << TTF_GetError() << "\n";
    }
    SDL_Color color = {0,0,0};
    SDL_Surface *surface = TTF_RenderText_Solid(timesNewRoman, name.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_Rect box;
    SDL_QueryTexture(texture, NULL, NULL, &box.w, &box.h);
    box.x =  SCREEN_WIDTH / 2 - box.w / 2;
    box.y =  40;
    SDL_RenderCopy(ren, texture, NULL, &box);
}
