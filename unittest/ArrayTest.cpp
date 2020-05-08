#include "gtest/gtest.h"

#include "ADT/Array.h"

TEST(Array, sizeOf) {
  EXPECT_EQ(sizeof(int)*2, sizeof(RawArray<int,2>)); 
  EXPECT_EQ(sizeof(int)*3, sizeof(RawArray<int,3>)); 
  EXPECT_EQ(sizeof(int)*4, sizeof(RawArray<int,4>)); 
  EXPECT_EQ(sizeof(float)*2, sizeof(RawArray<float,2>)); 
  EXPECT_EQ(sizeof(float)*3, sizeof(RawArray<float,3>)); 
  EXPECT_EQ(sizeof(float)*4, sizeof(RawArray<float,4>)); 
  EXPECT_EQ(sizeof(unsigned char)*5, sizeof(RawArray<unsigned char, 5>));
  EXPECT_EQ(sizeof(unsigned char)*4, sizeof(RawArray<unsigned char, 4>));
  EXPECT_EQ(sizeof(double)*7, sizeof(RawArray<double, 7>));
}

TEST(Array, init) {
  RawArray<int,2> arr(7, 101);
  EXPECT_EQ(arr[0], 7);
  EXPECT_EQ(arr[1], 101);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
