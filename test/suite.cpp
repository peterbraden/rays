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
  s->buildIndices();

  Intersection hit = s->nearestIntersection(
      (vec3) {0,0,0},
      (vec3) {0,0,1},
      100, 0
      );

  ASSERT_EQ(8, hit.distance);

  Intersection miss = s->nearestIntersection(
      (vec3) {0,0,0},
      (vec3) {0,0,-1},
      100, 0
      );

  ASSERT_EQ(-1, miss.distance);
}

TEST(Scenegraph, nearestIntersectionBasic2){
  SceneGraph *s = new SceneGraph();
  Sphere *a = new Sphere(
      (vec3) {0.,0.,10.}, 2., (Color) { 0, 0, 0});
  s->insertObject(a);
  Sphere *b = new Sphere(
      (vec3) {0.,10,10.}, 2., (Color) { 0, 0, 0});
  s->insertObject(b);
  s->buildIndices();

  Intersection hit = s->nearestIntersection(
      (vec3) {0,0,0},
      (vec3) {0,0,1},
      100, 0
      );

  ASSERT_EQ(8, hit.distance);

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
