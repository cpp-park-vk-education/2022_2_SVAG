#include <gtest/gtest.h>

#include "database.h"

TEST(Empty, TestEmpty) {
    print();
    EXPECT_EQ(1, 1);
}