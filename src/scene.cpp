typedef struct {
  Camera camera;
  std::vector<Sphere> objects;
} Scene;


Scene initScene (){
  Sphere a = Sphere((vec3) {0.,0.,-10.}, 2.);
  std::vector<Sphere> demoObjs;

  demoObjs.push_back(a);

  Camera defaultCamera = Camera((vec3) {0.,1.,0}, (vec3) {0.,10.,-50}, (vec3) {0.,0.,0.}, 0.78); // ~ pi/4

  Scene demoScene = {
    defaultCamera,
    demoObjs
  };
  return demoScene;
}

