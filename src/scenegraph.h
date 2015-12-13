#ifndef RAYS_SCENEGRAPH
#define RAYS_SCENEGRAPH
/*

# SceneGraph
- Use an octree for fast BBox intersection testing.
- Planes etc, with infinite BBox's must be tested seperately.


*/


#include <stdio.h>
#include <vector>
#include <math.h>
#include <limits>

#include "types.h"
#include "object.h"


typedef struct SceneGraphNode {
  int depth;
  BBox* bounds;

  vec3 mid;

  // Octree structure
  SceneGraphNode* children[8];
  std::vector<SceneObject*> objects;

  SceneGraphNode(BBox* b);
} SceneGraphNode;


class SceneGraph {
  private:
    // All Objects
    std::vector<SceneObject*> objects; 
    SceneGraphNode* root;

    // Infinite Objects (plane etc.)
    std::vector<SceneObject*> infiniteObjects;

    int partitionScene(SceneGraphNode* node , int maxDepth);

  public:
    SceneGraph() {};

    void insertObject(SceneObject* obj);
    void buildIndices();

    Intersection nearestIntersection(vec3 ro, vec3 rd, float max, float min);

    // Number of objects in scene. Informational.
    unsigned int size(); 
    
};
#endif
