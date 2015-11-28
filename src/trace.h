#ifndef RAYS_TRACE
#define RAYS_TRACE

#include <stdio.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <limits>

#include "types.h"
#include "material.h"
#include "scene.h"

typedef struct RenderStats {
  unsigned long raysTraced;
  time_t startTime;
  RenderStats(unsigned long i, time_t start): raysTraced(i), startTime(start) {};
} RenderStats;

Color trace(Ray r, int depth, Scene scene, RenderStats* stats);

#endif
