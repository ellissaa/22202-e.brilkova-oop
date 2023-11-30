#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(PopTests, PopBack1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.pop_back(), std::out_of_range);
}

TEST(PopTests, PopBack2) {
    CircularBuffer<int> cb(5);
    cb.push_back(10);
    
    int item = cb.pop_back();
    EXPECT_EQ(item, 10);
    EXPECT_EQ(cb.IsEmpty(), true);
}

TEST(PopTests, PopBack3) {
    CircularBuffer<int> cb(5);
    cb.push_back(10);
    cb.push_back(15);
    
    int item = cb.pop_back();

    EXPECT_EQ(item, 15);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 10);
    EXPECT_EQ(cb.front(), 10);
}

TEST(PopTests, PopBack4) {
    CircularBuffer<int> cb(5, 10);
    cb[1] = 1;
    cb[4] = 4;
    cb.push_back(15); // 15 (last) 1 (first) 10 10 4
    
    int item = cb.pop_back(); // _ 1 (first) 10 10 4 (last)

    EXPECT_EQ(item, 15);
    EXPECT_EQ(cb.size(), 4);
    EXPECT_EQ(cb.back(), 4);
    EXPECT_EQ(cb.front(), 1);
}

TEST(PopTests, PopFront1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.pop_front(), std::out_of_range);
}

TEST(PopTests, PopFront2) {
    CircularBuffer<int> cb(5);
    cb.push_front(10);
    
    int item = cb.pop_front();

    EXPECT_EQ(item, 10);
    EXPECT_EQ(cb.IsEmpty(), true);
}

TEST(PopTests, PopFront3) {
    CircularBuffer<int> cb(5);
    cb.push_front(10);
    cb.push_front(15);
    
    int item = cb.pop_front();

    EXPECT_EQ(item, 15);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 10);
    EXPECT_EQ(cb.front(), 10);
}

TEST(PopTests, PopFront4) {
    CircularBuffer<int> cb(5, 10);
    cb[0] = 0;
    cb[3] = 3;
    cb.push_front(15); // 0 10 10 3 (last) 15 (first)
    
    int item = cb.pop_front(); // 0 (first) 10 10 3 (last) _

    EXPECT_EQ(item, 15);
    EXPECT_EQ(cb.size(), 4);
    EXPECT_EQ(cb.back(), 3);
    EXPECT_EQ(cb.front(), 0);
}
