typedef struct {
  Camera camera;
  std::vector<Sphere> objects;
  float ambient; // Ambient light: 0 - 1;
  int maxDepth;
} Scene;


Scene initScene (){
  Sphere a = Sphere((vec3) {4.,0.,0.}, 2., (Color) { 0, 255, 0});
  Sphere b = Sphere((vec3) {-4.,0.,0.}, 2., (Color) {0, 0, 255});
  Sphere c = Sphere((vec3) {0.,4.,0.}, 2., (Color) {255, 0, 0});

  std::vector<Sphere> demoObjs;

  demoObjs.push_back(a);
  demoObjs.push_back(b);
  demoObjs.push_back(c);

  Camera defaultCamera = Camera((vec3) {0.,1.,0}, (vec3) {0.,0.,20}, (vec3) {0.,0.,0.}, 0.78); // ~ pi/4

  Scene demoScene = {
    defaultCamera,
    demoObjs,
    0.5, // Ambient
    1 // maxDepth
  };
  return demoScene;
}

