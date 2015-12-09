#include "scene.h"

Scene* initScene (int width, int height){
  SceneGraph* demoObjs = new SceneGraph();

  Sphere *a = new Sphere((vec3) {4.,4.,0.}, 2., (Color) { 0, 255, 0});
  Sphere *b = new Sphere((vec3) {-4.,4.,0.}, 2., (Color) {0, 0, 255});
  Sphere *c = new Sphere((vec3) {0.,8.,0.}, 2., (Color) {255, 0, 0});
  Sphere *d = new Sphere((vec3) {0.,0.,0.}, 2., (Color) {255, 0, 0});
  Sphere *e = new Sphere((vec3) {0.,4.,4.}, 2., (Color) {255, 0, 0});
  Sphere *f = new Sphere((vec3) {0.,4.,-4.}, 2., (Color) {255, 0, 0});

  Plane * surface = new Plane(-3.);

  demoObjs->insertObject(a);
  demoObjs->insertObject(b);
  demoObjs->insertObject(c);
  demoObjs->insertObject(d);
  demoObjs->insertObject(e);
  demoObjs->insertObject(f);
  demoObjs->insertObject(surface);

  for (int i = -50; i < 50; i++){
    Sphere *x = new Sphere((vec3) {(float)i*-4 + 4, 4, -25}, 2, (Color) {100,100,100});
    demoObjs->insertObject(x);

  }
  

  std::vector<PointLight>* demoLights = new std::vector<PointLight>();
  demoLights->push_back( (PointLight) { (vec3) {0., 10., 10.}, 0.7 } );
  demoLights->push_back( (PointLight) { (vec3) {10., 10., 0.}, 0.7 } );
  Camera* defaultCamera = new Camera((vec3) {0.,1.,0}, (vec3) {10,10,20}, (vec3) {0.,4.,0.}, 0.9, width, height); // ~ pi/4
  Scene *demoScene = new Scene(*defaultCamera, *demoObjs, *demoLights, 0.1, 2, width, height);
  return demoScene;
}

