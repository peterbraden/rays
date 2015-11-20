#include <math.h>
#include "camera.h"

Camera::Camera(vec3 u, vec3 loc, vec3 la, float a, int width, int height): angle(a){
  up = u;
  location = loc;
  lookat = la;

  camz = vec3_norm(vec3_sub(lookat, location));
  camx = vec3_norm(vec3_mul_cross(up, camz));

  camy = vec3_mul_cross(camx, vec3_sub((vec3) {0., 0., 0.}, camz));
  camy = vec3_norm(camy);

  tax = tan(angle);
  tay = tan(((float) height / (float) width) * angle);
}

// NB. Proportional x and y
Ray Camera::getRay(float x, float y){
  vec3 xdir;
  vec3 ydir;
  vec3 dest;

  xdir = vec3_scale(camx, (x-0.5) * tax);
  ydir = vec3_scale(camy, (y-0.5) * tay);

  dest = vec3_add(camz, vec3_add(xdir, ydir));

  Ray r;
  r.ro = location;
  r.rd = dest;

  return r;
}




