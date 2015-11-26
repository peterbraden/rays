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
#include <thread>
#endif

#include "types.h"
#include "material.h"
#include "object.h"
#include "camera.h"
#include "scene.cpp"
#include "trace.cpp"
#include "render.h"
#include "render.cpp"
#include "paint.cpp"
#include "trace.h"
#include "test.cpp"




Color renderAntiAliasedPixel(int x, int y, Scene scene){
  float x1 = (float) x / (float) scene.width;
  float x2 = ((float) x + 0.5)  / (float) scene.width;
  float y1 = (float) y / (float) scene.height;
  float y2 = ((float) y + 0.5)  / (float) scene.height;
  Ray ray1 = scene.camera.getRay(x1, y1);
  Ray ray2 = scene.camera.getRay(x1, y2);
  Ray ray3 = scene.camera.getRay(x2, y1);
  Ray ray4 = scene.camera.getRay(x2, y2);

  Color avg = trace(ray1, 0, scene);
  avg = color_add(avg, trace(ray2, 0, scene));
  avg = color_add(avg, trace(ray3, 0, scene));
  avg = color_add(avg, trace(ray4, 0, scene));

  avg = color_scale(avg, 0.25);

  return avg;
}


typedef struct {
  int i;
  RenderContext ctx;
  Scene scene;
} LineArgs;

void renderLine(void* vargs) {
  LineArgs* args = (LineArgs*) vargs;
  int i = args->i;
  RenderContext ctx = args->ctx;
  Scene scene = args->scene;
  for (int j = 0; j < scene.width; j++) {
    paintPixel(j, i, scene.width, scene.height, renderAntiAliasedPixel(j, i, scene),ctx);
    if (i%(scene.height/10) == 0 && j == 0) {
      printf("\nrender: %i/%i, traced: %i", i, scene.height, totalRaysTraced);
      updateScreen(ctx);
    }
  }
  updateScreen(ctx);
}


void paint(RenderContext ctx, Scene scene){
  for (int i = scene.height- 1; i >= 0 ; i--) {
    LineArgs args = (LineArgs) {i, ctx, scene};
//#ifdef __EMSCRIPTEN__
//    emscripten_async_call(renderLine, &args, 1);
//#else
    renderLine(&args);
//#endif
  }
}

void browserMainLoop(void* vargs){
  printf("browser tick\n");
  LineArgs* args = (LineArgs*) vargs;
  RenderContext ctx = *initScreen(args->scene.width, args->scene.height);
  args->ctx = ctx;
  renderLine(&args);
}

void renderBrowser(){
  #ifdef __EMSCRIPTEN__
  printf("Browser start");
  LineArgs args = (LineArgs) {0, NULL, *initScene()};
  emscripten_set_main_loop_arg(browserMainLoop, &args, 0, 0);

  #endif
}


void renderNative(){
  /*
  RenderContext ctx = *initScreen();
  Scene scene = *initScene();
  //for (int i = HEIGHT - 1; i >= 0 ; i--) {
    int i = 0;
   LineArgs args = (LineArgs) {i, ctx, scene};
    std::thread tl(renderLine, &args);
  //}
  tl.join();
  */
}


extern "C" int main(int argc, char** argv) {
  test();
  Scene* scene = initScene();
  printf("Initialised scene, %zu objects", scene->objects.size());

  #ifndef __EMSCRIPTEN__
  // render all as one.
  RenderContext* ctx = initScreen(scene->width, scene->height);
  paint(*ctx, *scene);
  printf("\nTotal Rays: %i\n", totalRaysTraced);
  //renderNative();
  saveScreen(ctx);
  #else
  paint(*initScreen(scene->width, scene->height), *scene);
  renderBrowser();
  #endif
  return 0;
}


