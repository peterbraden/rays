#include "types.h"
#include <math.h>
#include <stdio.h>


Color color_scale(Color a, float b){
  return (Color) {(int)((float) a.r * b),(int)((float)  a.g*b),(int)((float)  a.b * b)};
}

Color color_scale(Color a, vec3 b){
  return (Color) {(int)((float) a.r * b.x),(int) ((float) a.g*b.y),(int) ((float) a.b * b.z)};
}

Color color_add(Color a, Color b){
  return (Color) {a.r + b.r, a.g + b.g, a.b + b.b};
}
Color color_add(Color a, vec3 b){
  return (Color) {a.r +(int) b.x, a.g +(int) b.y, a.b + (int) b.z};
}

Color vec3_to_color(vec3 a){
  return (Color) {(int) a.x, (int) a.y, (int) a.z};
}

// Why the hell isnt' there a standard library for this.

vec3 vec3_add(vec3 a, vec3 b){
  vec3 r;
  r.x = a.x + b.x;
  r.y = a.y + b.y;
  r.z = a.z + b.z;
  return r;
} 

vec3 vec3_sub(vec3 a, vec3 b){
  vec3 r;
  r.x = a.x - b.x;
  r.y = a.y - b.y;
  r.z = a.z - b.z;
  return r;
} 

vec3 vec3_scale(vec3 v, float s) { 
  vec3 r;
  r.x = v.x * s;
  r.y = v.y * s;
  r.z = v.z * s;
  return r;
}

float vec3_mul_inner(vec3 a, vec3 b){
    float p = 0.;
    p += b.x * a.x;
    p += b.y * a.y;
    p += b.z * a.z;
    return p;
}

float vec3_dot(vec3 a, vec3 b){
  return vec3_mul_inner(a, b);
}

float vec3_len(vec3 const v){ \
  return sqrtf(vec3_mul_inner(v,v));
}

vec3 vec3_norm(vec3 in){
  return vec3_scale(in, 1.0 / vec3_len(in));
}

vec3 vec3_mul_cross(vec3 a, vec3  b){
  vec3 r;
  r.x = a.y*b.z - a.z*b.y;
  r.y = a.z*b.x - a.x*b.z;
  r.z = a.x*b.y - a.y*b.x;
  return r;
}

void vec3_print(vec3 a){
  printf("<%f, %f, %f>", a.x, a.y, a.z);
}


bool intersectsBBox(vec3 ro, vec3 invrd, BBox b){
  //http://tavianator.com/fast-branchless-raybounding-box-intersections/

  double tx1 = (b.min.x - ro.x)*invrd.x;
  double tx2 = (b.max.x - ro.x)*invrd.x;

  double tmin = fmin(tx1, tx2);
  double tmax = fmax(tx1, tx2);

  double ty1 = (b.min.y - ro.y)*invrd.y;
  double ty2 = (b.max.y - ro.y)*invrd.y;

  tmin = fmax(tmin, fmin(ty1, ty2));
  tmax = fmin(tmax, fmax(ty1, ty2));

  return tmax >= tmin;
}
vec3 vec3_invert(vec3 rd){
  return (vec3) {1.0/rd.x, 1.0/rd.y, 1.0/rd.z}; 
};

bool intersectsBBox(BBox a, BBox b){
  if (a.max.x < b.min.x) return false; // a is left of b
  if (a.min.x > b.max.x) return false; // a is right of b
  if (a.max.y < b.min.y) return false; // a is above b
  if (a.min.y > b.max.y) return false; // a is below b
  if (a.max.z < b.min.z) return false; // a is behind b
  if (a.min.z > b.max.z) return false; // a is in front of b
  return true; // boxes overlap
};

bool contains(BBox a, vec3 pt){
  if (pt.x < a.min.x || pt.x > a.max.x) return false;
  if (pt.y < a.min.y || pt.y > a.max.y) return false;
  if (pt.z < a.min.z || pt.z > a.max.z) return false;
  return true;
}




