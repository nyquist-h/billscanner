#include "gtest/gtest.h"

using namespace std;

TEST(BasicTest, Test) { 
    ASSERT_EQ (true, true);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

