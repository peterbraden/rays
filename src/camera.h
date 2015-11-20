#ifndef RAYS_CAMERA
#define RAYS_CAMERA

#include "types.h"

class Camera {
  private:
    vec3 camx;
    vec3 camy;
    vec3 camz;
    vec3 ncamz;
    float tax;
    float tay;

  public:
    vec3 up;
	  vec3 location;
	  vec3 lookat;
	  float angle;
	  Camera(vec3 u, vec3 loc, vec3 la, float a, int width, int height);
	  Ray getRay(float x, float y);
};

#endif
