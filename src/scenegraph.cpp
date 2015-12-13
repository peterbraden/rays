#include "scenegraph.h"

// HERO Algorithm

// From a ray's rd, calculate the VMask corresponding
// to the octant
unsigned int vmask(vec3 rd) {
  return (
      (rd.x < 0 ? 1 : 0) +
      (rd.y < 0 ? 2 : 0) +
      (rd.z < 0 ? 4 : 0)
      );
}

// BBox for octant inside bounds.
BBox* bboxFor(unsigned int oct, BBox bounds){
  // octant is Z, Y, X
  // => 000 is aligned to z,y,x min boundaries
  // => 111 is aligned to z,y,x max
  // => 001 is aligned to z,y min, x max.
  
  // Calc offset from min.
  int xoffs = oct & 1;
  int yoffs = oct & 2;
  int zoffs = oct % 4;

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

  return b;
}

// Get BBox[n] where the order of bboxes is determined by direction 
int bboxInd(unsigned int i, vec3 rd) {
  return (int) (i ^ vmask(rd)); // XOR
} // verified.

unsigned int maskdiff(vec3 l, float m){
  return (
    ((l.x < m ) ? 1 : 0 ) +
    ((l.y < m ) ? 2 : 0 ) +
    ((l.z < m ) ? 4 : 0 )
  );
}

bool isLeaf (SceneGraphNode* n){
  for (int i = 0; i<8;i++){
    if (n->children[i] != NULL)
      return false;
  }
  return true;
}


Intersection* searchLeaf (SceneGraphNode* leaf, vec3 ro, vec3 rd) {
  Intersection closest;
  closest.distance = std::numeric_limits<float>::max();
  bool intersects = false;

  for (int i = 0; i < leaf->objects.size(); i++){
    Intersection intersect = leaf->objects[i]->intersects(ro, rd);
    if (intersect.distance > 0 && 
        intersect.distance < closest.distance){
      closest = intersect;
      intersects = true;
    }
  }

  if (intersects){
    printf("!!! INTERSECTION\n");
    return new Intersection(closest); // TODO
  }
  return NULL;
}

unsigned int* genmasklist(float sxmid, float symid, float szmid) {
  unsigned int* masklist = new unsigned int[3];

  if (sxmid > symid){
    if (sxmid > szmid) {
      masklist[2] = 1;
      masklist[0] = ( symid > szmid ) ? 4 : 2;
      masklist[1] = ( symid > szmid ) ? 2 : 4;
    } else {
      masklist[1] = 1;
      masklist[0] = ( symid > szmid ) ? 4 : 2;
      masklist[2] = ( symid > szmid ) ? 2 : 4;
    }
  } else {
    masklist[0] = 1;
    masklist[1] = ( symid > szmid ) ? 4 : 2;
    masklist[2] = ( symid > szmid ) ? 2 : 4;
  }
  //printf("msk: %i,%i,%i \n", masklist[0], masklist[1], masklist[2]);
  return masklist;
}

unsigned int genraymin(int i, vec3 smid, unsigned int* masklist, unsigned int prevmin, unsigned int prevmax){
  if (i == -1){
    // Called for genraymax( i = 0)
    return prevmax;
  }
  if (i == 4){
    return prevmin;
  }

  switch (masklist[i]) {
    case 1:
      return smid.x;
    case 2:
      return smid.y;
    case 4:
      return smid.z;

    default:
      printf("!!!!!>>> ERROR RAYMIN: %i %i\n\n", i, masklist[i]);
      return 0;
  }
}

// HERO search hot loop.
Intersection* searchChild( SceneGraphNode* child,
                            vec3 ro,
                            vec3 rd,
                            vec3 invrd,
                            int depth,
                            float raymax,
                            float raymin,
                            unsigned int vm
                            ){

  printf("\n%*s %i search child:", depth, " ", depth);
  if (child == NULL){
    printf("ERROR search null child\n");
  }

  if (isLeaf(child)){
    printf("<<-leaf");
    return searchLeaf(child, ro, rd);
  }


  float sxmid = (child->mid.x - ro.x)*invrd.x;
  float symid = (child->mid.y - ro.y)*invrd.y;
  float szmid = (child->mid.z - ro.z)*invrd.z;
  vec3 smid = (vec3) {sxmid, symid, szmid};
  unsigned int childmask = maskdiff(smid, raymax);
  unsigned int lastmask = maskdiff(smid, raymin);
  unsigned int* masklist = genmasklist(sxmid, symid, szmid);

  //printf("\n childmask %i, lastmask %i", childmask, lastmask);
  //printf("\n smid: %.1f, %.1f, %.1f", sxmid, symid, szmid);
  //printf("\n masklist: %i %i %i", masklist[0], masklist[1], masklist[2]);

  unsigned int i = 0;
  while (i < 4) {
    //printf("\n %i : c: %i, mi: %i, m c^v %i \n", i, childmask, masklist[i], childmask ^ vm);
  
    unsigned int oldmask;

    unsigned int childraymax = genraymin(i - 1, smid, masklist, raymin, raymax);
    unsigned int childraymin = genraymin(i, smid, masklist, raymin, raymax); 

    if (child->children[childmask ^ vm] != NULL){
      Intersection* c = searchChild(
          child->children[childmask ^ vm],
          ro,
          rd,
          invrd,
          depth+1,
          childraymax,
          childraymin,
          vm);
      if (c != NULL) {
        return c;
      }
    }
    //printf("\n children were searched.. no match\n");

    if (childmask == lastmask) {
       //printf("hit last match. Exit\n");
       return NULL;
    } else {
      oldmask = masklist[i] & childmask;
      while ((masklist[i+1] & childmask) != oldmask) {
        i++;
        // continue while mask is same value.
        // ++i each iteration.
        if (i >= 3)
          return NULL; // Break out of outer while loop
      }
      childmask = childmask | masklist[i];
      //printf("childmask %i --> %i (%i)\n", oldmask, childmask, i);
      //printf("!! %i\n", masklist[i]);
    }
  }
  printf("Reached end of searchChild");
  return NULL;
}


Intersection* heroIntersection(SceneGraphNode* root, vec3 ro, vec3 rd){
  printf("\n -- Hero Intersection --");

  unsigned int vm = vmask(rd);
  vec3 invrd = vec3_invert(rd);
  float sxmin = (root->bounds->min.x - ro.x)*invrd.x;
  float symin = (root->bounds->min.y - ro.y)*invrd.y;
  float szmin = (root->bounds->min.z - ro.z)*invrd.z;
  float raymax = fmax(sxmin, fmax(symin, szmin));
  float sxmid = (root->mid.x - ro.x)*invrd.x;
  float symid = (root->mid.y - ro.y)*invrd.y;
  float szmid = (root->mid.z - ro.z)*invrd.z;
  vec3 smid = (vec3) {sxmid, symid, szmid};
  float sxmax = (root->bounds->max.x - ro.x)*invrd.x;
  float symax = (root->bounds->max.y - ro.y)*invrd.y;
  float szmax = (root->bounds->max.z - ro.z)*invrd.z;
  float raymin = fmin(sxmax, fmin(symax, szmax));

  printf("\nTrace Ray: [%.1f,%.1f,%.1f]->[%.1f,%.1f,%.1f]", ro.x, ro.y, ro.z, rd.x, rd.y, rd.z);

  return searchChild(root,
              ro, 
              rd, 
              invrd,
              0,
              raymax,
              raymin,
              vm
      );
}


void SceneGraph::insertObject(SceneObject* obj) {
  objects.push_back(obj);
}


SceneGraphNode* SceneGraph::nextLeaf(SceneGraphNode* curr, vec3 ro, vec3 rd) {
  return NULL;
}

Intersection SceneGraph::nearestIntersection(vec3 ro, vec3 rd, float max, float min){
  Intersection closest;
  closest.distance = max;
  bool intersects = false;

  // Search the Tree
  // 1. Is ro inside node->bounds?
  SceneGraphNode* node = root;
  bool inside = contains(*node->bounds, ro);
  heroIntersection(node, ro, rd);


/*
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
  */

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
  for (unsigned int i = 0; i < 8; i++){
    BBox* b = bboxFor(i, bounds);
     
    SceneGraphNode* n = new SceneGraphNode(b);
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


SceneGraphNode::SceneGraphNode(BBox* b) {
  bounds = b;
  mid = (vec3) {
    b->min.x + (b->max.x - b->min.x)/2,
    b->min.y + (b->max.y - b->min.y)/2,
    b->min.z + (b->max.z - b->min.z)/2,
  };

  for (int i = 0; i<8; i++){
    children[i] = NULL;
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

  root->depth = 0;
  int nodes = partitionScene(root, 10);


  printf("\nScene Graph:");
  printf("\n - Objects: %zu", objects.size());
  printf("\n - Infinite Objects: %zu", infiniteObjects.size());
  printf("\n - Bounded: <%.f,%.f,%.f> <%.f,%.f,%.f>", 
      sceneBounds->min.x, sceneBounds->min.y, sceneBounds->min.z,
      sceneBounds->max.x, sceneBounds->max.y, sceneBounds->max.z);
  printf("\n - Number of scene nodes: %i", nodes);


  printf("\n");
}



