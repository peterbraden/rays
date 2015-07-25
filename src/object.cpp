class SceneObject {
  public:
    virtual Intersection intersects(vec3 ro, vec3 rd) = 0;
    virtual void printInfo() = 0;
};

class Sphere: public SceneObject {
  private:
    vec3 center;
    float radius;

  public:
    Sphere(vec3 c, float r) : radius(r) {
      //printf("CREATE SPHERE %f", r);
      center = c;
    }

    Intersection intersects(vec3 ro, vec3 rd);
    void printInfo();

};

Intersection Sphere::intersects(vec3 ro, vec3 rd){
  //printf("Called Sphere::intersects, radius:  %f", radius);
  vec3 dst;

  dst = vec3_sub(ro, center);
  float b = vec3_mul_inner(dst, vec3_norm(rd)); // dot product.
  float c = vec3_mul_inner(dst, dst) - radius * radius;
  float d = b*b-c;
  float dist;

  //printf(">2 radius:  %f", radius); 
  if (d > 0){
    dist = -b - sqrt(d);
  } else {
    dist = -1;
  }

  //printf("-- %f %f %f %f --", b, c, d, dist);
  //printf(">3>>> %f", radius); 
  return (Intersection) {dist, {0,0,0}};
  
}
void Sphere::printInfo(){
  //printf("Sphere, radius: %f center:<%f,%f,%f> ", radius, center[0], center[1], center[2]);
}
