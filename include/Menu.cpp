#include <iostream>
#include "Menu.h"

int showmenu(SDL_Renderer* ren)
{
    // Background colour
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    TTF_Font* timesNewRoman = TTF_OpenFont("/home/mathi/workspace/advanced_c++/double_trouble/res/fonts/times_new_roman.ttf", 24);
    if (!timesNewRoman) {
        std::cout << TTF_GetError() << "\n";
    }
    int x, y;
    const int NUMMENU = 2;
    const char* labels[NUMMENU] = {"New Game","Exit"};
    SDL_Texture* menus[NUMMENU];
    bool selected[NUMMENU] = {false, false};
    SDL_Color color[2] = {{255,255,255},{255,0,0}};
    SDL_Rect pos[NUMMENU];
    for(int i = 0; i < NUMMENU; i += 1) {
        SDL_Surface *menuSurface = TTF_RenderText_Solid(timesNewRoman, labels[i], color[i]);
        menus[i] = SDL_CreateTextureFromSurface(ren, menuSurface);
        SDL_Rect textureBox;
        SDL_QueryTexture(menus[i], NULL, NULL, &textureBox.w, &textureBox.h);
        pos[i].x =  SCREEN_WIDTH / 2 - textureBox.w / 2;
        pos[i].y =  100 + i * 50;
        pos[i].h = textureBox.h;
        pos[i].w = textureBox.w;
        // TODO: enable this after test and check if it works
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
                    return 1;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for(int i = 0; i < NUMMENU; i += 1) {
                        if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
                        {
                            if(!selected[i])
                            {
                                selected[i] = true;
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman, labels[i], color[1]));
                            }
                        }
                        else
                        {
                            if(selected[i])
                            {
                                selected[i] = false;
                                SDL_DestroyTexture(menus[i]);
                                menus[i] = SDL_CreateTextureFromSurface(ren, TTF_RenderText_Solid(timesNewRoman, labels[i], color[0]));
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for(int i = 0; i < NUMMENU; i += 1) {
                        if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
                        {
                            SDL_DestroyTexture(menus[0]);
                            SDL_DestroyTexture(menus[1]);
                            return i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        SDL_DestroyTexture(menus[0]);
                        SDL_DestroyTexture(menus[1]);
                        return 0;
                    }
                    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
                        // TODO: add navigation through menu
                    }
                    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                        // TODO: add navigation through menu
                    }
            }
        }
        SDL_RenderClear(ren);
        for(int i = 0; i < NUMMENU; i++) {
            SDL_RenderCopy(ren, menus[i], NULL, &pos[i]);
        }
        SDL_RenderPresent(ren);
    }
}