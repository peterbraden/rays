#include "paint.h"

void updateScreen(RenderContext ctx){
#ifdef __EMSCRIPTEN__
  SDL_Flip(ctx.screen); 
#else
  SDL_UpdateWindowSurface(ctx.window);
#endif
}

void paintPixel(int x, int y, int width, int height, Color pix, RenderContext ctx){
  if (SDL_MUSTLOCK(ctx.screen)) SDL_LockSurface(ctx.screen);
  int alpha = 255;
  int sy = height - 1 - y;
  int offs = ctx.screen->pitch / sizeof(Uint32);
  int index = sy * offs + x;
  *((Uint32*)ctx.screen->pixels + index) = SDL_MapRGBA(ctx.screen->format, pix.r, pix.g, pix.b, alpha);
  if (SDL_MUSTLOCK(ctx.screen)) SDL_UnlockSurface(ctx.screen);
}

void initBackground(int width, int height, RenderContext ctx){
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int c = (j/2 + (i/2%2 == 0 ? 0 : 1)) % 2 == 0 ? 0 : 255;
      paintPixel(j, i, width, height, (Color) {c, c, c} ,ctx);
    }
  }
}

RenderContext* initOpenGLScreen(int width, int height) {
  #ifndef __EMSCRIPTEN__
  SDL_Window * window = SDL_CreateWindow("Rays", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, context);
  SDL_Surface *screen = SDL_GetWindowSurface(window);
  RenderContext* ctx = new RenderContext(screen, window);
  initBackground(width, height, *ctx);
  return ctx;
  #else
  return NULL;
  #endif
}

RenderContext* initOffscreenScreen(int width, int height) {
  #ifndef __EMSCRIPTEN__
  SDL_Surface *screen = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
  RenderContext* ctx = new RenderContext(screen, NULL);
  initBackground(width, height, *ctx);
  return ctx;
  #else
  return NULL;
  #endif
}

RenderContext* initScreen(int width, int height){
  SDL_Init(SDL_INIT_VIDEO);

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

#ifdef __EMSCRIPTEN__
  SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
  RenderContext* ctx = new RenderContext(screen);
  return ctx;
#else
  return initOffscreenScreen(width, height);
  //return initOpenGLScreen(width, height);
#endif
}

void saveScreen(RenderContext* ctx){
#ifndef __EMSCRIPTEN__
  if (ctx->window == NULL) {
    // Save image
    printf("Saving image\n");
    SDL_Surface *tmp = SDL_PNGFormatAlpha(ctx->screen);
    if(SDL_SavePNG(tmp, "screenshot.png")){
      printf("Unable to save png -- %s\n", SDL_GetError());
    }
    SDL_FreeSurface(tmp);
  } else {
    // Rendered in window, delay.
    SDL_Delay(5000);
  }
#else
  // Nothing to do in browser
#endif
}
