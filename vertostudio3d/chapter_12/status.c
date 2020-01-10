#include "status.h"
#include "main.h"
#include <stdio.h>

void init_status_lives(GameState *gameState)
{
    char str[128] = "";

    sprintf(str, "x %d", (int)gameState->man.lives);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *tmp = TTF_RenderText_Blended(gameState->font, str, white);
    gameState->labelW = tmp->w;
    gameState->labelH = tmp->h;
    // label is a SDL_Texture
    gameState->label = SDL_CreateTextureFromSurface(gameState->renderer, tmp);
    SDL_FreeSurface(tmp);
}

void draw_status_lives(GameState *gameState)
{
    //set the drawing color to black
    SDL_SetRenderDrawColor(gameState->renderer, 0, 0, 0, 255);

    //Clear the screen
    SDL_RenderClear(gameState->renderer);

    SDL_Rect rect = {320-70, 240-24, 48, 48};
    SDL_RenderCopyEx(gameState->renderer, gameState->manFrames[gameState->man.animFrame],
                     NULL, &rect, 0, NULL, (gameState->man.facingLeft == 0));

    //Set drawing color to white
    SDL_SetRenderDrawColor(gameState->renderer, 255, 255, 255, 255);

    //cannot access width and height from SDL_Texture but you can from a SDL_Surface
    SDL_Rect textRect = {320-20, 240 - gameState->labelH/2, gameState->labelW, gameState->labelH};
    SDL_RenderCopy(gameState->renderer, gameState->label, NULL, &textRect);
}

void shutdown_status_lives(GameState *gameState)
{
    SDL_DestroyTexture(gameState->label);
    //set this to NULL because it is optionall deleted later on.
    gameState->label = NULL;
}
