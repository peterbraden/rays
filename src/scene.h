#ifndef RAYS_SCENE
#define RAYS_SCENE

#include <stdio.h>
#include <vector>

#include "object.h"
#include "camera.h"
#include "scenegraph.h"

typedef struct Scene {
  Camera camera;
  SceneGraph objects;
  std::vector<PointLight> lights; // Should be generic light
  float ambient; // Ambient light: 0 - 1;
  int maxDepth;
  int width;
  int height;
  Scene (Camera c, SceneGraph o, std::vector<PointLight> l, float a, int d, int w, int h) : camera(c), objects(o), lights(l), ambient(a), maxDepth(d), width(w), height(h) {};
} Scene;

Scene* initScene ();
#endif
