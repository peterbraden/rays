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
    
#ifdef RAYS_TEST
    SceneGraphNode* getRoot();
#endif
};


#ifdef RAYS_TEST
// The following are exposed for unit testing, but don't make sense to use in isolation
unsigned int vmask(vec3 rd);
Intersection* naiveSearch(std::vector<SceneObject*> objects, vec3 ro, vec3 rd, float max, float min);
SceneGraphNode* searchForContaining(SceneGraphNode* node, vec3 ro);
Intersection* heroIntersection(SceneGraphNode* root, vec3 ro, vec3 rd);
BBox* bboxFor(unsigned int oct, BBox bounds);
Intersection* searchLeaf (SceneGraphNode* leaf, vec3 ro, vec3 rd);
#endif

#endif
