#include "SDL2/SDL.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO); //starts SDL2

    window = SDL_CreateWindow("Game Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              0
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    //Clear to blue
    SDL_RenderClear(renderer);

    //set color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect rect = {220, 140, 200, 200};
    SDL_RenderFillRect(renderer, &rect);

    //Done drawing present or show to screen
    SDL_RenderPresent(renderer);

    //Wait ebfore quitting program
    SDL_Delay(2000);

    //close/destroy window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    //clean up
    SDL_Quit();
    return 0;
}