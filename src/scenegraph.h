#ifndef RAYS_SCENEGRAPH
#define RAYS_SCENEGRAPH

#include <stdio.h>
#include <vector>
#include <math.h>
#include <limits>

#include "types.h"
#include "object.h"

class SceneGraph {
  private:
    std::vector<SceneObject*> objects; 

  public:
    SceneGraph() {};
    void insertObject(SceneObject* obj);
    Intersection nearestIntersection(vec3 ro, vec3 rd, float max, float min);

    // Number of objects in scene. Informational.
    unsigned int size(); 
    
};
#endif
