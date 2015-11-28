#include "scenegraph.h"

void SceneGraph::insertObject(SceneObject* obj) {
  objects.push_back(obj);
}

bool intersectsBBox(vec3 ro, vec3 invrd, BBox b){
  //http://tavianator.com/fast-branchless-raybounding-box-intersections/

  double tx1 = (b.min.x - ro.x)*invrd.x;
  double tx2 = (b.max.x - ro.x)*invrd.x;

  double tmin = fmin(tx1, tx2);
  double tmax = fmax(tx1, tx2);

  double ty1 = (b.min.y - ro.y)*invrd.y;
  double ty2 = (b.max.y - ro.y)*invrd.y;

  tmin = fmax(tmin, fmin(ty1, ty2));
  tmax = fmin(tmax, fmax(ty1, ty2));

  return tmax >= tmin;
}
vec3 invert(vec3 rd){
  return (vec3) {1.0/rd.x, 1.0/rd.y, 1.0/rd.z}; 
};


Intersection SceneGraph::nearestIntersection(vec3 ro, vec3 rd, float max, float min){
  Intersection closest;
  closest.distance = max;
  int intersects = 0;
  vec3 invrd = invert(rd);

  for(int i = objects.size()-1; i>=0; --i) {

    BBox* b = objects[i]->getBounds();
    if (b != NULL){
      if (!intersectsBBox(ro, invrd, *b)){
        continue;
      }
    }

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
