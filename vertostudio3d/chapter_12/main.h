//Will avoid the header getting included more than once
#ifndef sdl_testing_main_h
#define sdl_testing_main_h

#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2
#define NUM_STARS 100

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

typedef struct
{
  float x, y;
  float dx, dy;
  short lives;
  char *name;
  int onLedge;
  int isDead;
  
  int animFrame, facingLeft, slowingDown;
} Man;

typedef struct
{
  int x, y;
} Star;

typedef struct
{
  int x, y, w, h;
} Ledge;

typedef struct
{
  float scrollX;

  //Players
  Man man;
  
  //Stars
  Star stars[NUM_STARS];

  //Ledges
  Ledge ledges[100];
  
  //Images
  SDL_Texture *star;
  SDL_Texture *manFrames[2];
  SDL_Texture *brick;
  SDL_Texture *label;
  SDL_Texture *fire;
  int labelW, labelH;

  //Fonts
  TTF_Font *font;
  
  //time
  int time, deathCountdown;
  int statusState;
  
  //Renderer
  SDL_Renderer *renderer;
} GameState;

#endif // !
