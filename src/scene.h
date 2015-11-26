#ifndef RAYS_SCENE
#define RAYS_SCENE

#include "object.h"
#include "camera.h"

typedef struct Scene {
  Camera camera;
  std::vector<SceneObject*> objects; 
  std::vector<PointLight> lights; // Should be generic light
  float ambient; // Ambient light: 0 - 1;
  int maxDepth;
  int width;
  int height;
  Scene (Camera c, std::vector<SceneObject*> o, std::vector<PointLight> l, float a, int d, int w, int h) : camera(c), objects(o), lights(l), ambient(a), maxDepth(d), width(w), height(h) {};
} Scene;
#endif
