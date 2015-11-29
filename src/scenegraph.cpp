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

  // Search the Tree
  SceneGraphNode* node = root;
  if (intersectsBBox(ro, invrd, *node->bounds)){
    // if leaf
    for (int i = 0; i < node->objects.size(); i++){
      Intersection intersect = node->objects[i]->intersects(ro, rd);
      if (intersect.distance > 0 && 
          intersect.distance < closest.distance &&
          intersect.distance < max &&
          intersect.distance > min){
        closest = intersect;
        intersects = 1;
      }
    }
  }

  // Fall back to full intersection test for infinite objects.
  for(int i = infiniteObjects.size()-1; i>=0; --i) {
    Intersection intersect = infiniteObjects[i]->intersects(ro, rd);
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


void SceneGraph::partitionScene(SceneGraphNode* node, int maxDepth){
  // Octree equal child split.
  if (node->depth >= maxDepth){
    node->isLeaf = true;
    return;
  }
  
  for (int i = 0; i < 8; i++){
    // 
  }


}

void SceneGraph::buildIndices(){
  printf("\nbuilding Scene Graph");
  BBox* sceneBounds = new BBox(
      (vec3){0.,0.,0.},
      (vec3){0.,0.,0.}
      );

  root = new SceneGraphNode(sceneBounds);

  for (int i = 0; i < objects.size(); i++) {
    BBox* b = objects[i]->getBounds();
    if (b == NULL){
      // Object has no bounding box (boo...) so we can't optimise
      // it. Store it for iterative checking later.
      infiniteObjects.push_back(objects[i]);
      continue;
    }

    // Check if the object extends the scene's bounds
    if (b->min.x < sceneBounds->min.x) {
      sceneBounds->min.x = b->min.x;
    }
    if (b->min.y < sceneBounds->min.y) {
      sceneBounds->min.y = b->min.y;
    }
    if (b->min.z < sceneBounds->min.z) {
      sceneBounds->min.z = b->min.z;
    }
    if (b->max.x > sceneBounds->max.x) {
      sceneBounds->max.x = b->max.x;
    }
    if (b->max.y > sceneBounds->max.y) {
      sceneBounds->max.y = b->max.y;
    }
    if (b->max.z > sceneBounds->max.z) {
      sceneBounds->max.z = b->max.z;
    }

    root->objects.push_back(objects[i]);
  }



  printf("\nScene Graph:");
  printf("\n - Objects: %zu", objects.size());
  printf("\n - Infinite Objects: %zu", infiniteObjects.size());
  printf("\n - Bounded: <%.f,%.f,%.f> <%.f,%.f,%.f>", 
      sceneBounds->min.x, sceneBounds->min.y, sceneBounds->min.z,
      sceneBounds->max.x, sceneBounds->max.y, sceneBounds->max.z);


  printf("\n");
}



