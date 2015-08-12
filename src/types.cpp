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


Color color_scale(Color a, float b){
  return (Color) {a.r * b, a.g*b, a.b * b};
}

Color color_scale(Color a, vec3 b){
  return (Color) {a.r * b.x, a.g*b.y, a.b * b.z};
}

Color color_add(Color a, Color b){
  return (Color) {a.r + b.r, a.g + b.g, a.b + b.b};
}
Color color_add(Color a, vec3 b){
  return (Color) {a.r + b.x, a.g + b.y, a.b + b.z};
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
