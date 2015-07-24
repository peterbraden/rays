typedef struct {
  vec3 camera_location;
  int camera_distance;
  std::vector<Sphere> objects;
} Scene;






Scene initScene (){
  Sphere a = Sphere(0.,0.,-10., 2.);
  std::vector<Sphere> demoObjs;

  demoObjs.push_back(a);

  Scene demoScene = {
    {0.,0.,10.}, // camera_location
    5., // camera distance
    demoObjs
  };
  return demoScene;
}

