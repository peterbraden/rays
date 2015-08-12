/* Abstract the nightmare that is SDL1.2 and SDL2 CrossCompat. */

typedef struct {
  SDL_Surface* screen;
#ifndef __EMSCRIPTEN__
  SDL_Window* window;
#endif
} RenderContext;


void updateScreen(RenderContext ctx){
#ifdef __EMSCRIPTEN__
  SDL_Flip(ctx.screen); 
#else
  SDL_UpdateWindowSurface(ctx.window);
#endif
}

void paintPixel(int x, int y, Color pix, RenderContext ctx){
  if (SDL_MUSTLOCK(ctx.screen)) SDL_LockSurface(ctx.screen);
  int alpha = 255;
  int sy = HEIGHT - 1 - y;
  int offs = ctx.screen->pitch / sizeof(Uint32);
  int index = sy * offs + x;
  *((Uint32*)ctx.screen->pixels + index) = SDL_MapRGBA(ctx.screen->format, pix.r, pix.g, pix.b, alpha);
  if (SDL_MUSTLOCK(ctx.screen)) SDL_UnlockSurface(ctx.screen);
}

void initBackground(RenderContext ctx){
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int c = (j/2 + (i/2%2 == 0 ? 0 : 1)) % 2 == 0 ? 0 : 255;
      paintPixel(j, i, (Color) {c, c, c} ,ctx);
    }
  }
}

RenderContext initScreen(){
  SDL_Init(SDL_INIT_VIDEO);

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

#ifdef __EMSCRIPTEN__
  SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
  RenderContext ctx = {screen};
#else
  SDL_Window * window = SDL_CreateWindow("Rays", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, context);
  SDL_Surface *screen = SDL_GetWindowSurface(window);
  RenderContext ctx = {screen, window};
#endif 
  initBackground(ctx);
  return ctx;
}
