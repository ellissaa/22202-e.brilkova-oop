#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(PushTests, PushBack1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.push_back(10), std::out_of_range);
}

TEST(PushTests, PushBack2) {
    CircularBuffer<int> cb(5);
    cb.push_back(10);

    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 10);
    EXPECT_EQ(cb.front(), 10);
}

TEST(PushTests, PushBack3) {
    CircularBuffer<int> cb(5);
    cb.push_back(10);
    cb.push_back(15);

    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.back(), 15);
    EXPECT_EQ(cb.front(), 10);
}

TEST(PushTests, PushBack4) {
    CircularBuffer<int> cb(5, 10);
    cb[1] = 20;
    cb.push_back(15); // 15 (last) 20 (first) 10 10 10

    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.back(), 15);
    EXPECT_EQ(cb.front(), 20);
}

TEST(PushTests, PushFront1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.push_front(10), std::out_of_range);
}

TEST(PushTests, PushFront2) {
    CircularBuffer<int> cb(5);
    cb.push_front(10);

    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 10);
    EXPECT_EQ(cb.back(), 10);
}

TEST(PushTests, PushFront3) {
    CircularBuffer<int> cb(5);
    cb.push_front(10);
    cb.push_front(15);

    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.front(), 15);
    EXPECT_EQ(cb.back(), 10);
}

TEST(PushTests, PushFront4) {
    CircularBuffer<int> cb(5, 10);
    cb[3] = 20;
    cb.push_front(15); // 10 10 10 20 (last) 15 (first)

    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.front(), 15);
    EXPECT_EQ(cb.back(), 20);
}

TEST(PushTests, PushBackSum) {
    CircularBuffer<int> cb1(5, 10);
    CircularBuffer<int> cb2(6, 5);

    CircularBuffer<int> cb3 = cb1 + cb2;
    EXPECT_EQ(cb3.size(), 11);
    EXPECT_EQ(cb3.front(), 10);
    EXPECT_EQ(cb3.back(), 5);
    EXPECT_EQ(cb3[4], 10);
    EXPECT_EQ(cb3[5], 5);
}
