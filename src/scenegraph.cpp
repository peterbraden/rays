#include "scenegraph.h"

void SceneGraph::insertObject(SceneObject* obj) {
  objects.push_back(obj);
}

Intersection SceneGraph::nearestIntersection(vec3 ro, vec3 rd, float max, float min){
  Intersection closest;
  closest.distance = max;
  int intersects = 0;

  for(int i = objects.size()-1; i>=0; --i) {
    Intersection intersect = objects[i]->intersects(ro, rd);
    if (intersect.distance > 0 && 
        intersect.distance < closest.distance &&
        intersect.distance < max &&
        intersect.distance > min){
      closest = intersect;
      intersects = 1;
    }
  }

  if (intersects == 0){
    closest.distance = -1;
  }
  return closest;
}


unsigned int SceneGraph::size() {
  return objects.size();
}
