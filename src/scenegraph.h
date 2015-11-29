#ifndef RAYS_SCENEGRAPH
#define RAYS_SCENEGRAPH

#include <stdio.h>
#include <vector>
#include <math.h>
#include <limits>

#include "types.h"
#include "object.h"


typedef struct SceneGraphNode {
  int depth;
  BBox* bounds;
  bool isLeaf;
  // Octree structure
  SceneGraphNode* children[8];
  std::vector<SceneObject*> objects;

  SceneGraphNode(BBox* b): bounds(b) {};
} SceneGraphNode;


class SceneGraph {
  private:
    // All Objects
    std::vector<SceneObject*> objects; 

    SceneGraphNode* root;

    // Infinite Objects (plane etc.)
    std::vector<SceneObject*> infiniteObjects;

    void partitionScene(SceneGraphNode* node , int maxDepth);

  public:
    SceneGraph() {};

    void insertObject(SceneObject* obj);
    void buildIndices();

    Intersection nearestIntersection(vec3 ro, vec3 rd, float max, float min);

    // Number of objects in scene. Informational.
    unsigned int size(); 
    
};
#endif
