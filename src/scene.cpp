#include "scene.h"

Scene* initScene (){
  int width = 320;
  int height = 240;

  SceneGraph* demoObjs = new SceneGraph();

  Sphere *a = new Sphere((vec3) {4.,0.,0.}, 2., (Color) { 0, 255, 0});
  Sphere *b = new Sphere((vec3) {-4.,0.,0.}, 2., (Color) {0, 0, 255});
  Sphere *c = new Sphere((vec3) {0.,4.,0.}, 2., (Color) {255, 0, 0});

  Plane * surface = new Plane(-3.);

  demoObjs->insertObject(a);
  demoObjs->insertObject(b);
  demoObjs->insertObject(c);
  demoObjs->insertObject(surface);

  for (int i = 0; i < 50; i++){
    Sphere *x = new Sphere((vec3) {0.,0., (float)i*-4 + 4}, 2, (Color) {100,100,100});
    demoObjs->insertObject(x);

  }

  std::vector<PointLight>* demoLights = new std::vector<PointLight>();
  demoLights->push_back( (PointLight) { (vec3) {0., 10., 10.}, 0.7 } );
  Camera* defaultCamera = new Camera((vec3) {0.,1.,0}, (vec3) {20,5.,20}, (vec3) {0.,0.,0.}, 0.78, width, height); // ~ pi/4
  Scene *demoScene = new Scene(*defaultCamera, *demoObjs, *demoLights, 0.1, 2, width, height);
  return demoScene;
}

