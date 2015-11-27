#ifndef RAYS_TRACE
#define RAYS_TRACE

#include <stdio.h>
#include <vector>
#include <math.h>

#include "types.h"
#include "material.h"
#include "scene.h"

//extern unsigned int totalRaysTraced = 0;


std::vector<Intersection> intersect(vec3 ro, vec3 rd, Scene scene);
Intersection nearestIntersection(vec3 ro, vec3 rd, float max, float min, Scene scene);
Color trace(Ray r, int depth, Scene scene);

#endif
