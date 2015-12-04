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

  // Octree structure
  SceneGraphNode* children[8];
  SceneGraphNode* parent; // Faster traversal
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

    int partitionScene(SceneGraphNode* node , int maxDepth);

    // ## Bottom up octree traversal.
    // Given ray ro->rd find the next node along the ray. If node is null, then
    // find first node.
    // Assumes nodes are smallest intersecting bboxes.
    // Returns null if there's no more intersecting BBoxes.
    SceneGraphNode* nextLeaf(SceneGraphNode* curr, vec3 ro, vec3 rd);

  public:
    SceneGraph() {};

    void insertObject(SceneObject* obj);
    void buildIndices();

    Intersection nearestIntersection(vec3 ro, vec3 rd, float max, float min);

    // Number of objects in scene. Informational.
    unsigned int size(); 
    
};
#endif
