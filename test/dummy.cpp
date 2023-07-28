//
// Created by rohandev on 7/25/23.
//
#include "gtest/gtest.h"

// Demonstrate some basic assertions.
TEST(BasicTest, BasicAssertions) {
// Expect two strings not to be equal.
EXPECT_STRNE("Treeline", "Test");
// Expect equality.
EXPECT_EQ(7 * 6, 42);
}