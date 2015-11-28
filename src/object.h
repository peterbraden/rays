#ifndef RAYS_OBJECT
#define RAYS_OBJECT

#include "types.h"
#include "material.h"

class SceneObject {
  public:
    virtual Intersection intersects(vec3 ro, vec3 rd) = 0;
    virtual void printInfo() = 0;
    virtual Material material(vec3 pt) = 0;
    virtual BBox* getBounds() = 0;
};

class Sphere: public SceneObject {
  private:
    vec3 center;
    float radius;
    Material _material;

  public:
    Sphere(vec3 c, float r, Color col);
    vec3 normal(vec3 pt);
    Intersection intersects(vec3 ro, vec3 rd);
    BBox* getBounds();
    void printInfo();
    Material material(vec3 pt);
};

class Plane: public SceneObject {
  private:
    float y;
  public:
    Plane(float height);
    Material material(vec3 pt);
    Intersection intersects(vec3 ro, vec3 rd);
    void printInfo();
    BBox* getBounds();
};

typedef struct {
  vec3 location;
  float intensity;
} PointLight;

#endif
