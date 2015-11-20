#ifndef RAYS_TYPE
#define RAYS_TYPE

typedef struct {
  float x;
  float y;
  float z;
} vec3;

typedef struct {
  int r;
  int g;
  int b;
} Color;

typedef struct {
  vec3 ro;
  vec3 rd;
} Ray;

class SceneObject;
class Sphere;

typedef struct {
  float distance;
  vec3 point;
  vec3 normal;
  SceneObject* obj;
} Intersection;


Color color_scale(Color a, float b);
Color color_scale(Color a, vec3 b);
Color color_add(Color a, Color b);
Color color_add(Color a, vec3 b);
Color vec3_to_color(vec3 a);
// Why the hell isnt' there a standard library for this.
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_scale(vec3 v, float s);
float vec3_mul_inner(vec3 a, vec3 b);
float vec3_dot(vec3 a, vec3 b);
float vec3_len(vec3 const v);
vec3 vec3_norm(vec3 in);
vec3 vec3_mul_cross(vec3 a, vec3  b);
void vec3_print(vec3 a);

#endif