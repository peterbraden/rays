#include <stdio.h>
#include <vector>

#include "types.h"
#include "scene.h"
#include "trace.h"

void assertEqual(float x, float y, const char* m){
  if (x != y){
    printf("Error (float): %f != %f (%s)\n", x, y, m);
  }
}

void assertEqual(vec3 x, vec3 y, const char* m){
  assertEqual(x.x, y.x, m);
  assertEqual(x.y, y.y, m);
  assertEqual(x.z, y.z, m);
}

void assertEqual(SceneObject* x, SceneObject* y, const char* m){
  if (x != y) {
    printf("Error (scene obj): %p != %p (%s)\n", x, y, m);
  }
}

void test(){
  
  Sphere s = Sphere((vec3) {0.,0.,0}, 5., (Color) {100, 100, 100});
  Intersection i = s.intersects((vec3) {0,0,-10}, (vec3) {0,0,1});

  assertEqual(i.distance, 5., "Intersection distance");
  assertEqual(i.point, (vec3) {0,0,-5}, "Intersection point");
  assertEqual(i.normal, (vec3) {0,0,-1}, "Intersection normal");
  assertEqual(i.obj, &s, "Intersection object");
  

}
