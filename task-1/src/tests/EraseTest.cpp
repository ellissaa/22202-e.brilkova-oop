#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(EraseTests, Erase1) {
    CircularBuffer cb(10, 10);
    EXPECT_THROW(cb.erase(5, 20), std::out_of_range);
}

TEST(EraseTests, Erase2) {
    CircularBuffer cb(10, 10);
    EXPECT_NO_THROW(cb.erase(5, 10));
}

TEST(EraseTests, Erase3) {
    CircularBuffer cb(10, 10);
    cb.erase(5, 2);
    EXPECT_EQ(cb.size(), 10);
}

TEST(EraseTests, Erase4) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4);
    cb.push_back(5); // 1 (first) 2 3 4 5 (last)

    cb.erase(2, 4); // 1 (first) 2 5 (last) _ _
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 5);
}

TEST(EraseTests, Erase5) {
    CircularBuffer cb(5);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4);
    cb.push_back(5);

    cb.erase(0, 3); // 4 (first) 5 (last) _ _ _
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.front(), 4);
    EXPECT_EQ(cb.back(), 5);
}

TEST(EraseTests, Erase6) {
    CircularBuffer cb(5, 10);
    cb.erase(0, 5);
    EXPECT_EQ(cb.size(), 0);
}
