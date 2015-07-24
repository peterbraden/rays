#include <stdio.h>
#include <vector>
#include <math.h>
#include <SDL/SDL.h>
#include "../lib/linmath.h"
#include "types.cpp"
#include "object.cpp"
#include "scene.cpp"


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define WIDTH 10//6
#define HEIGHT 10//4


std::vector<Intersection> intersect(vec3 ro, vec3 rd, Scene scene){
  std::vector<Intersection> v;

  for(int i = scene.objects.size()-1; i>=0; --i) {
    printf("Iterate objects: %i of %zi \n", i, scene.objects.size());
    Intersection intersect = scene.objects[i].intersects(ro, rd);
    if (intersect.distance > 0){
      v.push_back(intersect);
    }
  }
  printf("Intersection %zi", v.size());

  return v;
}

// trace ro->rd into scene.
Color trace(vec3 ro, vec3 rd, int depth, Scene scene){
  std::vector<Intersection> intersections = intersect(ro, rd, scene);

  if (intersections.empty()){
    // No Intersection.
    return (Color) {0,0,0};
  }

  return (Color) {255, 255, 255};
}

Color paintPixel(int x, int y, Scene scene){
  vec3 lookat = {x-WIDTH/2, y - HEIGHT/2, 0};
  vec3 ray;
  vec3_sub(ray, lookat, scene.camera_location);
  printf("\n\n");
  Color pixel = trace(scene.camera_location, ray, 0, scene); 

  printf("\nRender <%i,%i> - %f,%f,%f : %i,%i,%i", x, y, ray[0], ray[1], ray[2], pixel.r, pixel.g, pixel.b);
  return pixel;
}

void paint(SDL_Surface* screen, Scene scene){
  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int alpha = 255;
      int index = i * WIDTH + j;
      Color pix = paintPixel(i, j, scene);
      *((Uint32*)screen->pixels + index) = SDL_MapRGBA(screen->format, pix.r, pix.g, pix.b, alpha);
    }
  }

  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_Flip(screen); 
}

extern "C" int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_VIDEO);

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

  SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

  paint(screen, initScene());
  //SDL_Quit();
  return 0;
}


