#include <stdio.h>
#include <SDL/SDL.h>
#include "../lib/linmath.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define WIDTH 600
#define HEIGHT 400


void paint(SDL_Surface* screen){
  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int alpha = 255;
      int index = i * WIDTH + j;
      *((Uint32*)screen->pixels + index) = SDL_MapRGBA(screen->format, i, j, 256-i, 255);
    }
  }

  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_Flip(screen); 
}

extern "C" int main(int argc, char** argv) {
  printf("hello, world!\n");
  
  SDL_Init(SDL_INIT_VIDEO);

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif


  SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

  paint(screen);

  SDL_Quit();
  return 0;
}


