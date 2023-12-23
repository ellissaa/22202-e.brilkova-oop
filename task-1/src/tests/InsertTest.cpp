#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(InsertTests, Insert1) {
    CircularBuffer cb;
    EXPECT_THROW(cb.insert(0, 20), std::out_of_range);
}

TEST(InsertTests, Insert2) {
    CircularBuffer cb(5);
    EXPECT_THROW(cb.insert(10, 20), std::out_of_range);
}

TEST(InsertTests, Insert3) {
    CircularBuffer cb(5);
    EXPECT_NO_THROW(cb.insert(0, 20));
}

TEST(InsertTests, Insert4) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2); // 1 (first) 2 (last) _ _ _

    cb.insert(1, 3); // 1 (first) 3 2 (last) _ _
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 2);
    EXPECT_EQ(cb[1], 3);
}

TEST(InsertTests, Insert5) {
    CircularBuffer cb(5);

    cb.insert(0, 3);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 3);
    EXPECT_EQ(cb.back(), 3);
}

TEST(InsertTests, Insert6) {
    CircularBuffer cb(5, 0);
    cb[1] = 1;
    cb[4] = 4; // 0 (first) 1 0 0 4 (last)

    cb.insert(2, 3); // 4 (last) 1 (first) 3 0 0
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 4);
    EXPECT_EQ(cb[1], 3);
}

TEST(InsertTests, Insert7) {
    CircularBuffer cb(5, 0);
    cb[1] = 1; // 0 (first) 1 0 0 0 (last)

    cb.insert(5, 3); // 3 (last) 1 (first) 0 0 0
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 3);
}
