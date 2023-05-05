#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    //Az SDL2 inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    //Az ablak és a renderer létrehozása
    SDL_Window* window = SDL_CreateWindow("Line Drawer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //Háttérszín beállítása
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    // Piros szín
    SDL_Rect redSquare = { 240, 0, 50, 50 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &redSquare);

    // Zöld szín
    SDL_Rect greenSquare = { 300, 0, 50, 50 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &greenSquare);

    // Kék szín
    SDL_Rect blueSquare = { 360, 0, 50, 50 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &blueSquare);

    //Váltó
    SDL_Rect changeMode = { 0, 0, 50, 50 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &changeMode);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect changeMode2 = { 0, 0, 50, 50 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawRect(renderer, &changeMode2);

    //Alap négyzet kirajzoláshoz
    SDL_Rect rect = {0, 0, 50, 50};

    //Frissítés
    SDL_RenderPresent(renderer);

    //Ideiglenes szín, alapszínek
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};
    SDL_Color tempColor = {0, 0, 0, 255};

    //Pontok
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1; 

    //SDL eventek, például bezárás, vonalak rajzolása
    SDL_Event event;
    bool quit = false;

    bool mode = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_RIGHT){
                        if(!mode){
                            if (x1 == -1 && y1 == -1){
                                x1 = event.button.x;
                                y1 = event.button.y;
                            } else {
                                x2 = event.button.x;
                                y2 = event.button.y;

                                //Pontok összekötése
                                SDL_SetRenderDrawColor(renderer, tempColor.r, tempColor.g, tempColor.b, 255);
                                SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

                                //Render frissítése
                                SDL_RenderPresent(renderer);

                                x1 = y1 = x2 = y2 = -1;
                            }
                        } else {
                            rect.x = event.button.x-25;
                            rect.y = event.button.y-25;

                            SDL_SetRenderDrawColor(renderer, tempColor.r, tempColor.g, tempColor.b, 255);
                            SDL_RenderFillRect(renderer, &rect);

                            //Render frissítése
                            SDL_RenderPresent(renderer);
                        }
                            
                    }
                    if(event.button.button == SDL_BUTTON_LEFT){
                        int x = event.button.x;
                        int y = event.button.y;
                        if(SDL_PointInRect(&(SDL_Point){x,y}, &redSquare)) {
                            tempColor = red;
                        } else if(SDL_PointInRect(&(SDL_Point){x,y}, &greenSquare)) {
                            tempColor = green;
                        } else if(SDL_PointInRect(&(SDL_Point){x,y}, &blueSquare)) {
                            tempColor = blue;
                        } else if(SDL_PointInRect(&(SDL_Point){x,y}, &changeMode)) {
                            if(!mode) {
                                mode = true;
                            } else {
                                mode = false;
                            }
                            
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}

