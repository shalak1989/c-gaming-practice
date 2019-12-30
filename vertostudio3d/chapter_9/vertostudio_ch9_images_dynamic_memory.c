#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Man
{
    int x, y;
    short life;
    char *name;
};

struct Star
{
    int x, y;
};

struct GameState
{
    //Players
    struct Man man;
    //this will create an array of 100 star structs
    struct Star stars[100];

    //Images, textures are the main type for images in SDL2
    SDL_Texture *star;
    SDL_Renderer *renderer;
};

void load_game(struct GameState *gameState)
{

    //This is the source image for what we will use to create our texture
    //Think of a surface of the "source pixels" in memory and think of the texture of the hardware accelerated texture you render with.
    SDL_Surface *starSurface = NULL;

    //Load images and create rendering textures from them
    starSurface = IMG_Load("star.png");
    if (starSurface == NULL)
    {
        printf("Cannot find star.png!\n\n");
        SDL_Quit();
        //closes program
        exit(1);
    }

    //store star in gamestate struct
    gameState->star = SDL_CreateTextureFromSurface(gameState->renderer, starSurface);
    //Once you create the image you don't need the surface anymore
    SDL_FreeSurface(starSurface);

    //This is now contained in larger gamestate object
    //struct Man man;
    gameState->man.x = 320 - 40;
    gameState->man.y = 240 - 40;

    //you may be tempted to use sizeof but when arrays are passed into functions they are pointers, so you would get the sizeof the pointer
    //this is why many functions that take arrays/array pointers in C also have a size argument you pass in.

    //initialize stars
    for (int i = 0; i < 100; i++)
    {
        //not sure why but the modulo operator here will give you between 0 and 639 and 0 and 479 now...
        gameState->stars[i].x = rand() %640;
        gameState->stars[i].y = rand() %480;
    }
}

int process_events(SDL_Window *window, struct GameState *gameState)
{
    SDL_Event event;
    int done = 0;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
                if (window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                }
                break;
            case SDL_QUIT:
                //quit game
                done = 1;
                break;
        }
    }

    //state is actually an array
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
    {
        gameState->man.x -= 10;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        gameState->man.x += 10;
    }
    if (state[SDL_SCANCODE_UP])
    {
        gameState->man.y -= 10;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        gameState->man.y += 10;
    }

    return done;
}

void do_render(SDL_Renderer *renderer, struct GameState *gameState)
{
    //set drawing color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    //Clear scren to blue
    SDL_RenderClear(renderer);

    //set drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Remember, rendering order matters, because of this code the star will always be on top of the square
    //drawing rectange at man's position
    SDL_Rect rect = {gameState->man.x, gameState->man.y, 200, 200};
    SDL_RenderFillRect(renderer, &rect);

    //draw star image
    for (int i = 0; i < 100; i++)
    {
        //you built out the stars position in another function, so now you can loop through the array to print them
        SDL_Rect starRect = {gameState->stars[i].x, gameState->stars[i].y, 64, 64};

        //Copy or draw SDL texture onto the renderer screen
        SDL_RenderCopy(renderer, gameState->star, NULL, &starRect);
    }

    //Done drawing present or show to screen
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    struct GameState gameState;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO); // starts SDL2

    //initializes system for using srand numbers
    //time will give you a different number, and you have to cast due to int size differences.
    //after this function is initialized somewhere... it looks like you can use it everywhere?

    //tutorial showed random() not sure why that works I only found srand (seed function) and rand
    srand((int)time(NULL));

    window = SDL_CreateWindow("Game Window",           //window title
                              SDL_WINDOWPOS_UNDEFINED, // initial x position
                              SDL_WINDOWPOS_UNDEFINED, // initial y position
                              640,                     // width, in pixels
                              480,                     // height, in pixels
                              0);                      // flags

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //storing renderer on gameState for easier access
    gameState.renderer = renderer;

    load_game(&gameState);

    // The window is open: enter program loop(See SDL_PollEvent)
    int done = 0;

    // basic SDL event loop below
    while (!done) // 0 evaluates to false so this works
    {
        // Check for events
        if (process_events(window, &gameState) == 1)
            done = 1;

        //render display
        do_render(renderer, &gameState);

        //PREVENTVSYNC flag in renderer makes this unnecessary
        //SDL_Delay(16);
    }

    //shutdown game and unload all memory
    SDL_DestroyTexture(gameState.star);

    // close/destroy window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // clean up
    SDL_Quit();
    return 0;
}
