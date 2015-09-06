#define WIDTH 400
#define HEIGHT 200

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
#include "types.cpp"
#include "material.cpp"
#include "object.cpp"
#include "camera.cpp"
#include "scene.cpp"
#include "trace.cpp"
#include "render.h"
#include "render.cpp"
#include "paint.cpp"
#include "test.cpp"



typedef struct {
  int i;
  RenderContext ctx;
  Scene scene;
} LineArgs;

void renderLine(void* vargs) {
  LineArgs* args = (LineArgs*) vargs;
  int i = args->i;
  RenderContext ctx = args->ctx;
  printf(">> %p \n", args);
  Scene s = args->scene;
  printf("!!\n");
  for (int j = 0; j < WIDTH; j++) {
    printf("render px: %i %i\n", i, j);
    paintPixel(j, i, renderPixelAA(j, i, s), ctx);
    if (i%2 == 0 && j == 0) {
      printf("\nrender: %i/%i", i, HEIGHT);
      updateScreen(ctx);
    }
  }
  updateScreen(ctx);
}


void paint(RenderContext ctx, Scene scene){
  for (int i = HEIGHT - 1; i >= 0 ; i--) {
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
  RenderContext ctx = *initScreen();
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
  #ifndef __EMSCRIPTEN__
  // render all as one.
  paint(*initScreen(), *initScene());
  printf("\nTotal Rays: %i\n", totalRaysTraced);
  //renderNative();
  SDL_Delay(5000);
  #else
  renderBrowser();
  #endif
  return 0;
}


