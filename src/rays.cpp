#define WIDTH 60
#define HEIGHT 40

#include <stdio.h>
#include <vector>
#include <math.h>
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
#include "types.cpp"
#include "object.cpp"
#include "camera.cpp"
#include "scene.cpp"
#include "paint.cpp"



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
Color trace(Ray r, int depth, Scene scene){
  std::vector<Intersection> intersections = intersect(r.ro, r.rd, scene);

  if (intersections.empty()){
    // No Intersection.
    return (Color) {0,0,0};
  }

  return (Color) {255, 255, 255};
}

Color renderPixel(int x, int y, Scene scene){
  Ray ray = scene.camera.getRay((float) x / (float) WIDTH, (float) y / (float) HEIGHT);

  Color pixel = trace(ray, 0, scene); 

  //printf("\nRender <%i,%i> - %f,%f,%f : %i,%i,%i", x, y, ray[0], ray[1], ray[2], pixel.r, pixel.g, pixel.b);
  return pixel;
}


void paint(RenderContext ctx, Scene scene){
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      paintPixel(i, j, renderPixel(i, j, scene),ctx);
      if (i%2 == 0 && j == 0) {
        printf("\nrender: %i/%i", i, HEIGHT);
        updateScreen(ctx);
      }
    }
  }
  updateScreen(ctx);
}

extern "C" int main(int argc, char** argv) {
  paint(initScreen(), initScene());

#ifndef __EMSCRIPTEN__
  SDL_Delay(2000);
#endif
  //SDL_Quit();
  return 0;
}


