#include "gtest/gtest.h"

#include "Math/Vector.h"

TEST(Vector, sizeOf) {
  EXPECT_EQ(sizeof(int)*2, sizeof(Vec2i)); 
  EXPECT_EQ(sizeof(int)*3, sizeof(Vec3i)); 
  EXPECT_EQ(sizeof(int)*4, sizeof(Vec4i)); 
  EXPECT_EQ(sizeof(float)*2, sizeof(Vec2f)); 
  EXPECT_EQ(sizeof(float)*3, sizeof(Vec3f)); 
  EXPECT_EQ(sizeof(float)*4, sizeof(Vec4f)); 
  EXPECT_EQ(sizeof(unsigned char)*5, sizeof(Vector<unsigned char, 5>));
  EXPECT_EQ(sizeof(unsigned char)*4, sizeof(Vector<unsigned char, 4>));
  EXPECT_EQ(sizeof(double)*7, sizeof(Vector<double, 7>));
}

TEST(Vector, basicVec3API) {
  Vec3f a;
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;

  EXPECT_EQ(1, a.x());
  EXPECT_EQ(2, a.y());
  EXPECT_EQ(3, a.z());

  Vec3f b;
  b.x() = 11;
  b.y() = 13;
  b.z() = 17;

  EXPECT_EQ(11, b[0]);
  EXPECT_EQ(13, b[1]);
  EXPECT_EQ(17, b[2]);

  Vec3f c;
  c.x(21);
  c.y(22);
  c.z(23);

  EXPECT_EQ(21, c[0]);
  EXPECT_EQ(22, c[1]);
  EXPECT_EQ(23, c[2]);

  Vec3f d(33,32,31);

  EXPECT_EQ(33, d[0]);
  EXPECT_EQ(32, d[1]);
  EXPECT_EQ(31, d[2]);

  //testing assignment with different types
  Vec3f e(40.f,41,42ul);

  EXPECT_EQ(40.f, e[0]);
  EXPECT_EQ(41.f, e[1]);
  EXPECT_EQ(42.f, e[2]);
}

TEST(Vector, addCopyVec2f) {
  Vec2f a, b, c;
  a[0] = 1;
  a[1] = 2;
  b[0] = 3;
  b[1] = 4;
  
  c = a+b;

  EXPECT_EQ(1, a[0]);	
  EXPECT_EQ(2, a[1]);	

  EXPECT_EQ(3, b[0]);	
  EXPECT_EQ(4, b[1]);	

  EXPECT_EQ(4, c[0]);	
  EXPECT_EQ(6, c[1]);	
}
