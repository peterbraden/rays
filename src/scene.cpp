typedef struct {
  Camera cam;
  std::vector<Sphere> objects;
} Scene;


Scene initScene (){
  Sphere a = Sphere(0.,0.,-10., 2.);
  std::vector<Sphere> demoObjs;

  demoObjs.push_back(a);

  Camera defaultCamera;
  defaultCamera.up = (vec3) {0.,1.,0};
  defaultCamera.location = (vec3) {0.,10.,-50};
  defaultCamera.lookat = (vec3) {0.,0.,0.};
  defaultCamera.angle = 0.78 // ~ pi/4

  Scene demoScene = {
    defaultCamera,
    demoObjs
  };
  return demoScene;
}

