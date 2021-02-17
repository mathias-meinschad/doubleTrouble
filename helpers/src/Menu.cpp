#include "Menu.hpp"

MenuEntries showSubMenu(SDL_Renderer *ren, int &currentLevel, int &levelsUnlocked) {
    levelsUnlocked = std::max(levelsUnlocked, 1);
    levelsUnlocked = std::min(levelsUnlocked, NR_OF_LEVELS);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    TTF_Font *timesNewRoman = TTF_OpenFont("res/fonts/times_new_roman.ttf", 24);
    if (!timesNewRoman) {
        std::cout << TTF_GetError() << "\n";
    }
    std::string labels[NR_OF_LEVELS];
    std::string levelString = "Level ";
    for (int i = 0; i < NR_OF_LEVELS; i++) {
        labels[i] = levelString + std::to_string(i + 1);
    }
    SDL_Texture *lockTexture = loadTexture(ren, "res/tiles/Other/lock.bmp");
    SDL_Texture *menus[NR_OF_LEVELS];
    int selectedEntry = 0;
    SDL_Color color[3] = {{255, 255, 255},
                          {255, 0,   0},
                          {100, 100, 100}};
    SDL_Rect pos[NR_OF_LEVELS];
    for (int i = 0; i < NR_OF_LEVELS; i++) {
        SDL_Surface *menuSurface;
        if (i >= levelsUnlocked) {
            menuSurface = TTF_RenderText_Solid(timesNewRoman, labels[i].c_str(), color[2]);
        } else {
            if (i == selectedEntry) {
                menuSurface = TTF_RenderText_Solid(timesNewRoman, labels[i].c_str(), color[1]);
            } else {
                menuSurface = TTF_RenderText_Solid(timesNewRoman, labels[i].c_str(), color[0]);
            }
        }
        menus[i] = SDL_CreateTextureFromSurface(ren, menuSurface);
        SDL_Rect textureBox;
        SDL_QueryTexture(menus[i], nullptr, nullptr, &textureBox.w, &textureBox.h);
        pos[i].x = SCREEN_WIDTH / 2 - textureBox.w / 2;
        pos[i].y = 100 + i * 50;
        pos[i].h = textureBox.h;
        pos[i].w = textureBox.w;
        SDL_FreeSurface(menuSurface);
    }

    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    for (auto &menu : menus) {
                        SDL_DestroyTexture(menu);
                    }
                    return EXIT;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        for (auto &menu : menus) {
                            SDL_DestroyTexture(menu);
                        }
                        return PREVIOUS_MENU;
                    }
                    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
                        selectedEntry = (selectedEntry - 1 + levelsUnlocked) % levelsUnlocked;
                        for (int i = 0; i < levelsUnlocked; i++) {
                            if (i == selectedEntry) {
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman,
                                                                                                  labels[i].c_str(),
                                                                                                  color[1]));
                            } else {
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman,
                                                                                                  labels[i].c_str(),
                                                                                                  color[0]));
                            }
                        }
                    }
                    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                        selectedEntry = (selectedEntry + 1) % levelsUnlocked;
                        for (int i = 0; i < levelsUnlocked; i++) {
                            if (i == selectedEntry) {
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman,
                                                                                                  labels[i].c_str(),
                                                                                                  color[1]));
                            } else {
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman,
                                                                                                  labels[i].c_str(),
                                                                                                  color[0]));
                            }
                        }
                    }
                    if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN ||
                        event.key.keysym.sym == SDLK_SPACE) {
                        for (auto &menu : menus) {
                            SDL_DestroyTexture(menu);
                        }
                        currentLevel = selectedEntry;
                        return SELECT_LEVEL;
                    }
            }
        }
        SDL_RenderClear(ren);
        for (int i = 0; i < NR_OF_LEVELS; i++) {
            if (i >= levelsUnlocked) {
                Position lockPosition(pos[i].x - 40, pos[i].y);
                renderTexture(lockTexture, ren, lockPosition, 0.05);
            }
            SDL_RenderCopy(ren, menus[i], nullptr, &pos[i]);
        }
        SDL_RenderPresent(ren);
    }
}

MenuEntries showMainMenu(SDL_Renderer *ren, int &currentLevel, int &levelsUnlocked) {
    // Background colour
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    TTF_Font *timesNewRoman = TTF_OpenFont(
            "res/fonts/times_new_roman.ttf", 24);
    if (!timesNewRoman) {
        std::cout << TTF_GetError() << "\n";
    }
    const char *labels[NR_MENU_ITEMS] = {"New Game", "Select Level", "Exit"};
    SDL_Texture *menus[NR_MENU_ITEMS];
    int selectedEntry = 0;
    SDL_Color color[2] = {{255, 255, 255},
                          {255, 0,   0}};
    SDL_Rect pos[NR_MENU_ITEMS];
    for (int i = 0; i < NR_MENU_ITEMS; i += 1) {
        SDL_Surface *menuSurface;
        if (i == selectedEntry) {
            menuSurface = TTF_RenderText_Solid(timesNewRoman, labels[i], color[1]);
        } else {
            menuSurface = TTF_RenderText_Solid(timesNewRoman, labels[i], color[0]);
        }
        menus[i] = SDL_CreateTextureFromSurface(ren, menuSurface);
        SDL_Rect textureBox;
        SDL_QueryTexture(menus[i], nullptr, nullptr, &textureBox.w, &textureBox.h);
        pos[i].x = SCREEN_WIDTH / 2 - textureBox.w / 2;
        pos[i].y = 100 + i * 50;
        pos[i].h = textureBox.h;
        pos[i].w = textureBox.w;
        SDL_FreeSurface(menuSurface);
    }

    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    for (auto &menu : menus) {
                        SDL_DestroyTexture(menu);
                    }
                    return EXIT;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        for (auto &menu : menus) {
                            SDL_DestroyTexture(menu);
                        }
                        return EXIT;
                    }
                    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
                        selectedEntry = (selectedEntry - 1 + 3) % NR_MENU_ITEMS;
                        for (int i = 0; i < NR_MENU_ITEMS; i++) {
                            if (i == selectedEntry) {
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren,
                                                                        TTF_RenderText_Solid(timesNewRoman, labels[i],
                                                                                             color[1]));
                            } else {
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren,
                                                                        TTF_RenderText_Solid(timesNewRoman, labels[i],
                                                                                             color[0]));
                            }
                        }
                    }
                    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                        selectedEntry = (selectedEntry + 1) % NR_MENU_ITEMS;
                        for (int i = 0; i < NR_MENU_ITEMS; i++) {
                            if (i == selectedEntry) {
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren,
                                                                        TTF_RenderText_Solid(timesNewRoman, labels[i],
                                                                                             color[1]));
                            } else {
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren,
                                                                        TTF_RenderText_Solid(timesNewRoman, labels[i],
                                                                                             color[0]));
                            }
                        }
                    }
                    if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN ||
                        event.key.keysym.sym == SDLK_SPACE) {
                        switch (selectedEntry) {
                            case 0:
                                currentLevel = 0;
                                return NEW_GAME;
                            case 1: {
                                currentLevel = 1;
                                MenuEntries subMenuResult = showSubMenu(ren, currentLevel, levelsUnlocked);
                                switch (subMenuResult) {
                                    case SELECT_LEVEL:
                                        for (auto &menu : menus) {
                                            SDL_DestroyTexture(menu);
                                        }
                                        return SELECT_LEVEL;
                                    case EXIT:
                                        for (auto &menu : menus) {
                                            SDL_DestroyTexture(menu);
                                        }
                                        return EXIT;
                                    default:
                                        break;
                                }
                                break;
                            }
                            case 2:
                            default:
                                for (auto &menu : menus) {
                                    SDL_DestroyTexture(menu);
                                }
                                return EXIT;
                        }
                    }
            }
        }
        SDL_RenderClear(ren);
        for (int i = 0; i < NR_MENU_ITEMS; i++) {
            SDL_RenderCopy(ren, menus[i], nullptr, &pos[i]);
        }
        SDL_RenderPresent(ren);
    }
}
