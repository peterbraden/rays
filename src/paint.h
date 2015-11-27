#ifndef RAYS_PAINT
#define RAYS_PAINT

#include "types.h"

#ifdef __EMSCRIPTEN__
#  include <emscripten.h>
#  include <SDL/SDL.h>
#else
#  include <SDL2/SDL.h>
#  include <stdio.h>
#  include "sdl-savepng/savepng.h"
#  ifdef __APPLE__
#    include <OpenGL/gl.h>
#    include <OpenGL/glu.h>
#    include <GLUT/glut.h>
#  else
#    include <GL/gl.h>
#    include <GL/glu.h>
#    include <GL/glut.h>
#  endif
#endif



/* Abstract the nightmare that is SDL1.2 and SDL2 CrossCompat. */

typedef struct RenderContext{
  SDL_Surface* screen;
#ifndef __EMSCRIPTEN__
  SDL_Window* window;
  RenderContext(SDL_Surface* s, SDL_Window* w) : screen(s), window(w) {}
# else 
  RenderContext(SDL_Surface* s) : screen(s) {}
#endif
} RenderContext;


RenderContext* initScreen(int width, int height);
void paintPixel(int x, int y, int width, int height, Color pix, RenderContext ctx);
void updateScreen(RenderContext ctx);
void saveScreen(RenderContext* ctx);

#endif
