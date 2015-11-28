#include "scene.h"


Scene* initScene (){
  int width = 600;
  int height = 400;

  Sphere *a = new Sphere((vec3) {4.,0.,0.}, 2., (Color) { 0, 255, 0});
  Sphere *b = new Sphere((vec3) {-4.,0.,0.}, 2., (Color) {0, 0, 255});
  Sphere *c = new Sphere((vec3) {0.,4.,0.}, 2., (Color) {255, 0, 0});

  Plane * surface = new Plane(-3.);

  std::vector<SceneObject*>* demoObjs = new std::vector<SceneObject*>();

  demoObjs->push_back(a);
  demoObjs->push_back(b);
  demoObjs->push_back(c);
  demoObjs->push_back(surface);

  for (int i = 0; i < 50; i++){
    Sphere *x = new Sphere((vec3) {0.,0., (float)i*-4 + 4}, 2, (Color) {100,100,100});
    demoObjs->push_back(x);

  }

  std::vector<PointLight>* demoLights = new std::vector<PointLight>();
  demoLights->push_back( (PointLight) { (vec3) {0., 10., 10.}, 0.7 } );
  Camera* defaultCamera = new Camera((vec3) {0.,1.,0}, (vec3) {20,5.,20}, (vec3) {0.,0.,0.}, 0.78, width, height); // ~ pi/4
  Scene *demoScene = new Scene(*defaultCamera, *demoObjs, *demoLights, 0.1, 2, width, height);
  return demoScene;
}

