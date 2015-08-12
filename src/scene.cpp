typedef struct {
  Camera camera;
  std::vector<SceneObject*> objects; 
  std::vector<PointLight> lights; // Should be generic light
  float ambient; // Ambient light: 0 - 1;
  int maxDepth;
} Scene;


Scene initScene (){
  Sphere *a = new Sphere((vec3) {4.,0.,0.}, 2., (Color) { 0, 255, 0});
  Sphere *b = new Sphere((vec3) {-4.,0.,0.}, 2., (Color) {0, 0, 255});
  Sphere *c = new Sphere((vec3) {0.,4.,0.}, 2., (Color) {255, 0, 0});

  std::vector<SceneObject*> demoObjs;

  demoObjs.push_back(a);
  demoObjs.push_back(b);
  demoObjs.push_back(c);
  
  std::vector<PointLight> demoLights;
  demoLights.push_back( (PointLight) { (vec3) {0, 10, 10}, 0.7 } );

  Camera defaultCamera = Camera((vec3) {0.,1.,0}, (vec3) {0.,0.,20}, (vec3) {0.,0.,0.}, 0.78); // ~ pi/4

  Scene demoScene = {
    defaultCamera,
    demoObjs,
    demoLights,
    0.1, // Ambient
    1 // maxDepth
  };
  return demoScene;
}

