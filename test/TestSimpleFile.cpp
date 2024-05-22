#include <gtest/gtest.h>
#include "SimpleFile.h"

TEST(MyMathTest, Add) {
    ASSERT_EQ(add(1, 1), 2);
    ASSERT_EQ(add(-1, 1), 0);
    ASSERT_EQ(add(-1, -1), -2);
}
