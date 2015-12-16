#include "gtest/gtest.h"
#include "types.h"
#include "scene.h"
#include "scenegraph.h"

TEST(Vector, Inverse) {
  vec3 i = (vec3) {1., 2., 4};
  vec3 j = vec3_invert(i);
  EXPECT_EQ(1, j.x);
  EXPECT_EQ(0.5, j.y);
  EXPECT_EQ(0.25, j.z);
}

TEST(Scenegraph, vmask){
  vec3 i = (vec3) {1, -2, 3};
  unsigned int j = vmask(i);
  EXPECT_EQ(2, j);
}


TEST(Scenegraph, nearestIntersectionBasic){
  SceneGraph *s = new SceneGraph();
  Sphere *a = new Sphere(
      (vec3) {0.,0.,10.}, 2., (Color) { 0, 0, 0});
  s->insertObject(a);

  Sphere *b = new Sphere(
      (vec3) {0.,10,10.}, 2., (Color) { 0, 0, 0});

  s->insertObject(b);
  s->buildIndices();

  SceneGraphNode* root = s->getRoot();

  // Check scene bbox
  EXPECT_EQ(6, root->bounds->max.x);
  EXPECT_EQ(-2, root->bounds->min.x);
  EXPECT_EQ(12, root->bounds->max.y);
  EXPECT_EQ(-2, root->bounds->min.y);
  EXPECT_EQ(12, root->bounds->max.z);
  EXPECT_EQ(0, root->bounds->min.z);

  // Check Structure of octree
  // sphere in xmin, ymax zmax => 110 -> 6
  // sphere in xmin, ymin, zmax => 100 -> 4
  EXPECT_EQ(NULL, root->children[0]);
  EXPECT_EQ(NULL, root->children[1]);
  EXPECT_EQ(NULL, root->children[2]);
  EXPECT_EQ(NULL, root->children[3]);
  EXPECT_TRUE(NULL != root->children[4]);
  EXPECT_EQ(NULL, root->children[5]);
  EXPECT_TRUE(NULL != root->children[6]);
  EXPECT_EQ(NULL, root->children[7]);


  Intersection hit = s->nearestIntersection(
      (vec3) {0,0,0},
      (vec3) {0,0,1},
      100, 0
      );

  EXPECT_EQ(8, hit.distance);

  Intersection miss = s->nearestIntersection(
      (vec3) {0,0,0},
      (vec3) {0,0,-1},
      100, 0
      );

  ASSERT_EQ(-1, miss.distance);

  Intersection* hit2 = searchLeaf(s->getRoot(),
      (vec3) {0,0,0},
      (vec3) {0,0,1});

  ASSERT_EQ(8, hit2->distance);

}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
