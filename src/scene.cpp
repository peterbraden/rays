typedef struct Scene {
  Camera camera;
  std::vector<SceneObject*> objects; 
  std::vector<PointLight> lights; // Should be generic light
  float ambient; // Ambient light: 0 - 1;
  int maxDepth;
  Scene (Camera c, std::vector<SceneObject*> o, std::vector<PointLight> l, float a, int d) : camera(c), objects(o), lights(l), ambient(a), maxDepth(d) {}; 
} Scene;


Scene* initScene (){
  Sphere *a = new Sphere((vec3) {4.,0.,0.}, 2., (Color) { 0, 255, 0});
  Sphere *b = new Sphere((vec3) {-4.,0.,0.}, 2., (Color) {0, 0, 255});
  Sphere *c = new Sphere((vec3) {0.,4.,0.}, 2., (Color) {255, 0, 0});

  Plane * surface = new Plane(-3.);

  std::vector<SceneObject*>* demoObjs = new std::vector<SceneObject*>();

  demoObjs->push_back(a);
  demoObjs->push_back(b);
  demoObjs->push_back(c);
  demoObjs->push_back(surface);
  
  
  std::vector<PointLight>* demoLights = new std::vector<PointLight>();
  demoLights->push_back( (PointLight) { (vec3) {0., 10., 10.}, 0.7 } );

  Camera* defaultCamera = new Camera((vec3) {0.,1.,0}, (vec3) {20,5.,20}, (vec3) {0.,0.,0.}, 0.78); // ~ pi/4

  Scene *demoScene = new Scene(*defaultCamera, *demoObjs, *demoLights, 0.1, 2);
  return demoScene;
}

