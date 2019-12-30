#include "SDL2/SDL.h"
#include <stdio.h>

// I read that typedef struct can be bad practice, without it you would need to
// go struct Man instead of using it like a built in type
struct Man
{
    int x, y;
    short life;
    char *name;
};

int process_events(SDL_Window *window, struct Man *man)
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

                        // The below code would make it act like you were typing the arrow keys as opposed to holding it, not really good for continuous smooth action
                        //SDL_SCANCODE is better for that and shown further down

                        // case SDLK_RIGHT:
                        //     man->x += 10;
                        //     break;
                        // case SDLK_LEFT:
                        //     man->x -= 10;
                        //     break;
                        // case SDLK_UP:
                        //     man->y -= 10;
                        //     break;
                        // case SDLK_DOWN:
                        //     man->y += 10;
                        //     break;
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
        man->x -= 10;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        man->x += 10;
    }
    if (state[SDL_SCANCODE_UP])
    {
        man->y -= 10;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        man->y += 10;
    }

    return done;
}

void do_render(SDL_Renderer *renderer, struct Man *man)
{
    //set drawing color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    //Clear scren to blue
    SDL_RenderClear(renderer);

    //set drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect rect = {man->x, man->y, 200, 200};
    SDL_RenderFillRect(renderer, &rect);

    //Done drawing present or show to screen
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    struct Man man;
    man.x = 220;
    man.y = 140;

    SDL_Init(SDL_INIT_VIDEO); // starts SDL2

    window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // The window is open: enter program loop(See SDL_PollEvent)
    int done = 0;

    // basic SDL event loop below
    while (!done) // 0 evaluates to false so this works
    {
        // Check for events
        if (process_events(window, &man) == 1)
            done = 1;

        //render display
        do_render(renderer, &man);

        //don't burn up the CPU and so we need a delay on the rendering (this is 1000/100 or 10 frames a second, for 60 FPS roughly 16.67 ms )
        SDL_Delay(16);
    }

    // close/destroy window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // clean up
    SDL_Quit();
    return 0;
}
