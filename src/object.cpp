class SceneObject {
  public:
    virtual Intersection intersects(vec3 ro, vec3 rd) = 0;
    virtual void printInfo() = 0;
    virtual Color color(vec3 pt) = 0;
};

class Sphere: public SceneObject {
  private:
    vec3 center;
    float radius;
    Color col;

  public:
    Sphere(vec3 c, float r) : radius(r) {
      center = c;
      col = (Color) {255, 0, 100};
    }

    vec3 normal(vec3 pt);
    Intersection intersects(vec3 ro, vec3 rd);
    void printInfo();
    Color color(vec3 pt);

};

vec3 Sphere::normal(vec3 pt){
  return vec3_norm(vec3_sub(pt, center));
}

Color Sphere::color(vec3 pt){
  return col;
}

Intersection Sphere::intersects(vec3 ro, vec3 rd){
  //printf("Called Sphere::intersects, radius:  %f", radius);
  vec3 dst;
  vec3 pt;

  dst = vec3_sub(ro, center);
  float b = vec3_mul_inner(dst, vec3_norm(rd)); // dot product.
  float c = vec3_mul_inner(dst, dst) - radius * radius;
  float d = b*b-c;
  float dist;

  if (d > 0){
    dist = -b - sqrt(d);
  } else {
    dist = -1;
  }

  // Project point along ray
  pt = vec3_add(ro, vec3_scale(vec3_norm(rd), dist));
  return (Intersection) {dist, pt, normal(pt), this};
}

void Sphere::printInfo(){
  printf("Sphere, radius: %f center:<%f,%f,%f> ", radius, center.x, center.y, center.z);
}
