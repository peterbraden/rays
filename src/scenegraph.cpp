#include "scenegraph.h"

void SceneGraph::insertObject(SceneObject* obj) {
  objects.push_back(obj);
}


SceneGraphNode* SceneGraph::nextLeaf(vec3 ro, vec3 rd) {
  return NULL;
}

Intersection SceneGraph::nearestIntersection(vec3 ro, vec3 rd, float max, float min){
  Intersection closest;
  closest.distance = max;
  bool intersects = false;
  vec3 invrd = vec3_invert(rd);

  // Search the Tree
  // 1. Is ro inside node->bounds?
  SceneGraphNode* node = root;
  bool inside = contains(*node->bounds, ro);

  if (intersectsBBox(ro, invrd, *node->bounds)){
    // if leaf
    for (int i = 0; i < node->objects.size(); i++){
      Intersection intersect = node->objects[i]->intersects(ro, rd);
      if (intersect.distance > 0 && 
          intersect.distance < closest.distance &&
          intersect.distance < max &&
          intersect.distance > min){
        closest = intersect;
        intersects = true;
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
      intersects = true;
    }
  }

  if (intersects == false){
    closest.distance = -1;
  }
  return closest;
}


unsigned int SceneGraph::size() {
  return objects.size();
}



// Octree equal child split.
int SceneGraph::partitionScene(SceneGraphNode* node, int maxDepth){
  BBox bounds = *node->bounds;

  printf("\n%*s -> [%.f,%.f,%.f] [%.f,%.f,%.f] %i objects", 
      node->depth*4, " ",
      bounds.min.x, bounds.min.y, bounds.min.z,
      bounds.max.x, bounds.max.y, bounds.max.z,
      node->objects.size());
  
  int subnodes = 1;
  // Create children;
  for (int i = 0; i < 8; i++){
    // Calc top corner offset
    int xoffs = i % 2;
    int yoffs = (i / 2) % 2;
    int zoffs = (i / 4) % 2;
    float xdiff = bounds.max.x - bounds.min.x;
    float ydiff = bounds.max.y - bounds.min.y;
    float zdiff = bounds.max.z - bounds.min.z;
    float xmin = bounds.min.x + (xoffs ? xdiff/2 : 0);
    float ymin = bounds.min.y + (yoffs ? ydiff/2 : 0);
    float zmin = bounds.min.z + (zoffs ? zdiff/2 : 0);
    float xmax = bounds.min.x + (xoffs ? xdiff : xdiff/2 );
    float ymax = bounds.min.y + (yoffs ? ydiff : ydiff/2 );
    float zmax = bounds.min.z + (zoffs ? zdiff : zdiff/2 );
    BBox* b = new BBox(
        (vec3) {xmin, ymin, zmin},
        (vec3) {xmax, ymax, zmax}
        ); 
     
    SceneGraphNode* n = new SceneGraphNode(b);
    n->parent = node;
    n->depth = node->depth + 1;

    // Which objects are in this new BBox?
    for (int j = 0; j< node->objects.size(); j++) {
    
      if (intersectsBBox(*b, *node->objects[j]->getBounds())){
        // TODO CACHE
        n->objects.push_back(node->objects[j]);
      }
    }

    if (n->depth >= maxDepth) continue;
    if (n->objects.size() == 0) continue; // Empty leaf node;
    
    node->children[i] = n;

    if (n->objects.size() > 1){
      subnodes += partitionScene(n, maxDepth);
    }
  }

  return subnodes;
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

  root->depth = 0;
  int nodes = partitionScene(root, 2);


  printf("\nScene Graph:");
  printf("\n - Objects: %zu", objects.size());
  printf("\n - Infinite Objects: %zu", infiniteObjects.size());
  printf("\n - Bounded: <%.f,%.f,%.f> <%.f,%.f,%.f>", 
      sceneBounds->min.x, sceneBounds->min.y, sceneBounds->min.z,
      sceneBounds->max.x, sceneBounds->max.y, sceneBounds->max.z);
  printf("\n - Number of scene nodes: %i", nodes);


  printf("\n");
}



