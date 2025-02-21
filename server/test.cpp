#include "test/test.h"
#include "world/geo.h"

TEST(Intersect) {
  using namespace world;
  Vec P[3][3] = {
      {{0, 0}, {0, 1}, {0, 2}},
      {{1, 0}, {1, 1}, {1, 2}},
      {{2, 0}, {2, 1}, {2, 2}},
  };
  {
    Line a(P[0][0], P[2][2]);
    Line b(P[2][0], P[0][2]);

    auto c = a.Intersect(b);
    EXPECT_TRUE(c.has_value());
    EXPECT_EQ(c.value(), P[1][1]);
  }
  {
    Line a(P[0][0], P[1][1]);
    Line b(P[2][0], P[0][2]);

    auto c = a.Intersect(b);
    EXPECT_TRUE(c.has_value());
  }
  {
    Line a(P[0][0], P[1][1]);
    Line b(P[2][0], P[1][2]);

    auto c = a.Intersect(b);
    EXPECT_FALSE(c.has_value());
  }
  {
    Line a(P[0][0], P[1][1]);
    Line b(P[1][0], P[2][1]);

    auto c = a.Intersect(b);
    EXPECT_FALSE(c.has_value());
  }
}

int main(int argc, char** argv) {
  TEST_Intersect();
  return 0; 
}