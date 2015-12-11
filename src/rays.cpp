#include <time.h>
#include <unistd.h>

#include "types.h"
#include "material.h"
#include "object.h"
#include "camera.h"
#include "render.h"
#include "trace.h"
#include "paint.h"
#include "scene.h"
#include "scenegraph.h"


void paint(RenderContext ctx, Scene scene, RenderStats* stats){
  for (int i = scene.height- 1; i >= 0 ; i--) {
    for (int j = 0; j < scene.width; j++) {

      paintPixel(j, i, scene.width, scene.height, renderAntiAliasedPixel(j, i, scene, stats),ctx);

      if (scene.height > 10 && i%(scene.height/10) == 0 && j == 0) {
        printf("\nrender: %i/%i, traced: %zu", i, scene.height, stats->raysTraced);
        updateScreen(ctx);
      }
    }
  }
}


extern "C" int main(int argc, char** argv) {
  // Parse Command Line Args...
  int width = 300;
  int height = 200;
  int opt = 0;
  while ((opt = getopt(argc, argv, "w:h:")) != -1) {
    switch (opt) {
        case 'w':
            width = atoi(optarg);
            break;
        case 'h':
            height = atoi(optarg);
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-w width] [-h height] name\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
  }

  Scene* scene = initScene(width, height);

  scene->objects.buildIndices();
  printf("Initialised scene, %i objects", scene->objects.size());


  time_t start;
  time(&start);
  RenderStats* stats = new RenderStats(0, start);
  RenderContext* ctx = initScreen(scene->width, scene->height);

  // render all as one.
  paint(*ctx, *scene, stats);

  time_t finish;
  time(&finish);
  double elapsed = difftime(finish, start);

  printf("\nImage: %ix%i  Total Rays: %zu (avg pp: %zu)\n",
      scene->width, scene->height, stats->raysTraced,
      stats->raysTraced / (scene->width * scene->height));

  printf("\n%.f seconds (%.f rays per sec)\n",
      elapsed, stats->raysTraced / elapsed);

  #ifndef __EMSCRIPTEN__
  saveScreen(ctx);
  #else
  renderBrowser();
  #endif

  return 0;
}


