#define WIDTH 200
#define HEIGHT 100

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
#include "material.cpp"
#include "object.cpp"
#include "camera.cpp"
#include "scene.cpp"
#include "paint.cpp"
#include "test.cpp"



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

Intersection nearestIntersection(vec3 ro, vec3 rd, Scene scene){
  Intersection closest;
  closest.distance = std::numeric_limits<float>::max();
  int intersects = 0;

  for(int i = scene.objects.size()-1; i>=0; --i) {
    Intersection intersect = scene.objects[i].intersects(ro, rd);
    if (intersect.distance > 0 && intersect.distance < closest.distance){
      closest = intersect;
      intersects = 1;
    }
  }

  if (intersects == 0){
    closest.distance = -1;
  }
  return closest;
}

// trace ro->rd into scene.
Color trace(Ray r, int depth, Scene scene){

  Intersection closest = nearestIntersection(r.ro, r.rd, scene);

  if (closest.distance < 0) {
    // No Intersection.
    return (Color) {0,0,0};
  }

  Material material = closest.obj->material(closest.point);
  Color out;


  // Ambient
  out = color_scale(material.pigment, scene.ambient);

  // Diffuse (Lambertian)
  // Specular
  // Reflection
  if (depth < scene.maxDepth){ // TODO - only if reflection != 0
    Ray refl;
    refl.ro = closest.point;
    refl.rd = vec3_sub(r.rd, vec3_scale(closest.normal, 2.0 * vec3_dot(closest.normal, r.rd)));
    Color rc = trace(refl, depth + 1, scene);
    out = color_add(color_scale(out, 1 - material.reflection), color_scale(rc, material.reflection)); 
  }
  

  return out;
}

Color renderPixel(int x, int y, Scene scene){
  Ray ray = scene.camera.getRay((float) x / (float) WIDTH, (float) y / (float) HEIGHT);

  Color pixel = trace(ray, 0, scene); 

  //printf("\nRender <%i,%i>: %i,%i,%i", x, y, pixel.r, pixel.g, pixel.b);
  return pixel;
}


void paint(RenderContext ctx, Scene scene){
  for (int i = HEIGHT - 1; i >= 0 ; i--) {
    for (int j = 0; j < WIDTH; j++) {
      paintPixel(j, i, renderPixel(j, i, scene),ctx);
      if (i%2 == 0 && j == 0) {
        printf("\nrender: %i/%i", i, HEIGHT);
        updateScreen(ctx);
      }
    }
  }
  updateScreen(ctx);
}

extern "C" int main(int argc, char** argv) {
  test();
  paint(initScreen(), initScene());

#ifndef __EMSCRIPTEN__
  SDL_Delay(200);
#endif
  SDL_Quit();
  return 0;
}


