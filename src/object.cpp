class SceneObject {
  public:
    virtual Intersection intersects(vec3 ro, vec3 rd) = 0;
    virtual void printInfo() = 0;
    virtual Material material(vec3 pt) = 0;
};

class Sphere: public SceneObject {
  private:
    vec3 center;
    float radius;
    Material _material;

  public:
    Sphere(vec3 c, float r, Color col) : radius(r) {
      center = c;
      _material.pigment = col;
      _material.reflection = 0.5;
      _material.phong = 40;
    }

    vec3 normal(vec3 pt);
    Intersection intersects(vec3 ro, vec3 rd);
    void printInfo();
    Material material(vec3 pt);

};

class Plane: public SceneObject {
  private:
    float y;
  public:
    Plane(float height) : y(height) {}
    Intersection intersects(vec3 ro, vec3 rd);
    //Material material(vec3 pt);
};


Intersection Plane::intersects(vec3 ro, vec3 rd){
  vec3 rdn = vec3_norm(rd);
  vec3 norm = (vec3) {0,1,0};
  float dist = vec3_dot( norm, vec3_sub( (vec3) {0,y,0}, ro));
  dist = dist / vec3_dot(norm, rdn);
  vec3 pt = vec3_add(ro, vec3_scale(vec3_norm(rd), dist));

  return (Intersection) {dist, pt, norm, this};

}




vec3 Sphere::normal(vec3 pt){
  return vec3_norm(vec3_sub(pt, center));
}

Material Sphere::material(vec3 pt){
  return _material;
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


typedef struct {
  vec3 location;
  float intensity;
} PointLight;

