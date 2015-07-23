class SceneObject {
  public:
    virtual Intersection intersects(vec3 ro, vec3 rd){
      return (Intersection) {-1, {0,0,0}};
    };
};

class Sphere: public SceneObject {
  private:
    vec3 center;
    float radius;

  public:
    Sphere(vec3 c, float r){
      printf("CREATE SPHERE %f", r);
      center[0] = c[0];
      center[1] = c[1];
      center[2] = c[2];
      radius = r;
    }

    Intersection intersects(vec3 ro, vec3 rd);

};

Intersection Sphere::intersects(vec3 ro, vec3 rd){
  printf(">1>>> %f", radius);
  vec3 rdn;
  vec3 dst;

  vec3_norm(rdn, rd);
  vec3_sub(dst, ro, center);
  float b = vec3_mul_inner(dst, rdn); // dot product.
  float c = vec3_mul_inner(dst, dst) - radius * radius;
  float d = b*b-c;
  float dist;

  printf(">2>>> %f", radius); 
  if (d > 0){
    dist = -b - sqrt(d);
  } else {
    dist = -1;
  }

  //printf("-- %f %f %f %f --", b, c, d, dist);
  printf(">3>>> %f", radius); 
  return (Intersection) {dist, {0,0,0}};
  
}
