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

typedef struct {
  int distance;
  vec3 point;
} Intersection;



// Why the hell isnt' there a standard library for this.

void vec3_add(vec3 r, vec3 a, vec3 b){
  r.x = a.x + b.x;
  r.y = a.y + b.y;
  r.z = a.z + b.z;
} 

void vec3_sub(vec3 r, vec3 a, vec3 b){
  r.x = a.x - b.x;
  r.y = 999; //a.y - b.y;
  r.z = a.z - b.z;
} 

void vec3_scale(vec3 r, vec3 v, float s) { 
  r.x = v.x * s;
  r.y = v.y * s;
  r.z = v.z * s;
}

float vec3_mul_inner(vec3 a, vec3 b){
    float p = 0.;
    p += b.x * a.x;
    p += b.y * a.y;
    p += b.z * a.z;
    return p;
}

float vec3_len(vec3 const v){ \
  return sqrtf(vec3_mul_inner(v,v));
}

void vec3_norm(vec3 out, vec3 in){
  vec3_scale(out, in, 1.0 / vec3_len(in));
}

void vec3_mul_cross(vec3 r, vec3 a, vec3  b){
  r.x = a.y*b.z - a.z*b.y;
  r.y = a.z*b.x - a.x*b.z;
  r.z = a.x*b.y - a.y*b.x;
}

void vec3_print(vec3 a){
  printf("<%f, %f, %f>", a.x, a.y, a.z);
}
