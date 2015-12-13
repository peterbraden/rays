#include "gtest/gtest.h"
#include "types.h"

TEST(Vector, Inverse) {
  vec3 i = (vec3) {1., 2., 4};
  vec3 j = vec3_invert(i);
  EXPECT_EQ(1, j.x);
  EXPECT_EQ(0.5, j.y);
  EXPECT_EQ(0.25, j.z);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
