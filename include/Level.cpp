#include "Level.hpp"

Level::Level(std::string &filePath, SDL_Texture *wallTexture, SDL_Texture *staticEnemyTexture) {
    std::ifstream inputFile(filePath);
    if (!inputFile) {
        // TODO remove this
        std::cout << "Failed to load Level1" << "\n";
    }
    std::string line;
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
        walls.emplace_back(Coordinates(x,y+350), wallTexture, scale);
    }

    getline(inputFile, line);
    while (getline(inputFile, line)) {
        if (3 != std::sscanf(line.c_str(),"%d,%d,%f", &x, &y, &scale)) {
            std::cout << "Check level file \n";
        }
        staticEnemies.emplace_back(Coordinates(x, y), staticEnemyTexture, scale);
    }
}