#include <iostream>
#include "Menu.h"



MenuEntries showmenu(SDL_Renderer* ren)
{
    // Background colour
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    TTF_Font* timesNewRoman = TTF_OpenFont("/home/mathi/workspace/advanced_c++/double_trouble/res/fonts/times_new_roman.ttf", 24);
    if (!timesNewRoman) {
        std::cout << TTF_GetError() << "\n";
    }
    const char* labels[NR_MENU_ITEMS] = {"New Game", "Select Level", "Exit"};
    SDL_Texture* menus[NR_MENU_ITEMS];
    int selectedEntry = 0;
    SDL_Color color[2] = {{255,255,255},{255,0,0}};
    SDL_Rect pos[NR_MENU_ITEMS];
    for(int i = 0; i < NR_MENU_ITEMS; i += 1) {
        SDL_Surface *menuSurface;
        if (i == selectedEntry) {
            menuSurface = TTF_RenderText_Solid(timesNewRoman, labels[i], color[1]);
        } else {
            menuSurface = TTF_RenderText_Solid(timesNewRoman, labels[i], color[0]);
        }
        menus[i] = SDL_CreateTextureFromSurface(ren, menuSurface);
        SDL_Rect textureBox;
        SDL_QueryTexture(menus[i], NULL, NULL, &textureBox.w, &textureBox.h);
        pos[i].x =  SCREEN_WIDTH / 2 - textureBox.w / 2;
        pos[i].y =  100 + i * 50;
        pos[i].h = textureBox.h;
        pos[i].w = textureBox.w;
        SDL_FreeSurface(menuSurface);
    }
    
    SDL_Event event;
    while(true)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    SDL_DestroyTexture(menus[0]);
                    SDL_DestroyTexture(menus[1]);
                    return EXIT;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        SDL_DestroyTexture(menus[0]);
                        SDL_DestroyTexture(menus[1]);
                        return EXIT;
                    }
                    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
                        SDL_DestroyTexture(menus[selectedEntry]);
                        menus[selectedEntry] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman, labels[selectedEntry], color[0]));
                        selectedEntry = (selectedEntry - 1 + 3) % NR_MENU_ITEMS;
                        SDL_DestroyTexture(menus[selectedEntry]);
                        menus[selectedEntry] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman, labels[selectedEntry], color[1]));
                    }
                    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                        SDL_DestroyTexture(menus[selectedEntry]);
                        menus[selectedEntry] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman, labels[selectedEntry], color[0]));
                        selectedEntry = (selectedEntry + 1) % NR_MENU_ITEMS;
                        SDL_DestroyTexture(menus[selectedEntry]);
                        menus[selectedEntry] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman, labels[selectedEntry], color[1]));
                    }
                    if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN) {
                        switch (selectedEntry) {
                            case 0:
                                return NEW_GAME;
                            case 1:
                                return SELECT_LEVEL;
                            case 2:
                            default:
                                return EXIT;
                        }
                    }
            }
        }
        SDL_RenderClear(ren);
        for(int i = 0; i < NR_MENU_ITEMS; i++) {
            SDL_RenderCopy(ren, menus[i], NULL, &pos[i]);
        }
        SDL_RenderPresent(ren);
    }
}