#include <stdio.h>
#include <vector>
#include <math.h>
#include "../lib/linmath.h"
#include "types.cpp"
#include "object.cpp"
#include "scene.cpp"


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#else 
#include <SDL2/SDL.h>
#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#endif

#define WIDTH 600
#define HEIGHT 400

// FML native interfaces are nasty.
typedef struct {
  SDL_Surface* screen;
#ifndef __EMSCRIPTEN__
  SDL_Window* window;
#endif
} RenderContext;

std::vector<Intersection> intersect(vec3 ro, vec3 rd, Scene scene){
  std::vector<Intersection> v;

  for(int i = scene.objects.size()-1; i>=0; --i) {
    //printf("Iterate objects: %i of %zi \n", i, scene.objects.size());
    Intersection intersect = scene.objects[i].intersects(ro, rd);
    if (intersect.distance > 0){
      v.push_back(intersect);
    }
  }
  //printf("Intersection %zi", v.size());

  return v;
}

// trace ro->rd into scene.
Color trace(vec3 ro, vec3 rd, int depth, Scene scene){
  std::vector<Intersection> intersections = intersect(ro, rd, scene);

  if (intersections.empty()){
    // No Intersection.
    return (Color) {100,0,0};
  }

  return (Color) {255, 255, 255};
}

Color paintPixel(int x, int y, Scene scene){
  vec3 lookat = {x-WIDTH/2, y - HEIGHT/2, 0};
  vec3 ray;
  vec3_sub(ray, lookat, scene.camera_location);
  //printf("\n\n");
  Color pixel = trace(scene.camera_location, ray, 0, scene); 

  //printf("\nRender <%i,%i> - %f,%f,%f : %i,%i,%i", x, y, ray[0], ray[1], ray[2], pixel.r, pixel.g, pixel.b);
  return pixel;
}

void updateScreen(RenderContext ctx){
#ifdef __EMSCRIPTEN__
  SDL_Flip(ctx.screen); 
#else
  SDL_UpdateWindowSurface(ctx.window);
#endif
}

void paint(RenderContext ctx, Scene scene){
  if (SDL_MUSTLOCK(ctx.screen)) SDL_LockSurface(ctx.screen);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int alpha = 255;
      int index = i * WIDTH + j;
      Color pix = paintPixel(i, j, scene);
      *((Uint32*)ctx.screen->pixels + index) = SDL_MapRGBA(ctx.screen->format, pix.r, pix.g, pix.b, alpha);
      if (index%300 == 0) {
        updateScreen(ctx);
      }
    }
  }

  if (SDL_MUSTLOCK(ctx.screen)) SDL_UnlockSurface(ctx.screen);
}





extern "C" int main(int argc, char** argv) {
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

  paint(ctx, initScene());

#ifndef __EMSCRIPTEN__
  SDL_Delay(2000);
#endif
  //SDL_Quit();
  return 0;
}


