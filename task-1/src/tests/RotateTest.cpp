#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(RotateTests, Linearize1) {
    CircularBuffer<int> cb;
    EXPECT_EQ(cb.linearize(), nullptr);
}

TEST(RotateTests, Linearize2) {
    CircularBuffer<int> cb(4);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4);
    cb.push_back(5);
    cb.push_back(6); // 5 6 (last) 3 (first) 4
    
    int* buffer = cb.buffer();
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);
    
    cb.linearize(); // 3 (first) 4 5 6 (last)
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 5);
    EXPECT_EQ(buffer[3], 6);
}

TEST(RotateTests, Rotate1) {
    CircularBuffer<int> cb(5);
    EXPECT_THROW(cb.rotate(0), std::out_of_range);
}

TEST(RotateTests, Rotate2) {
    CircularBuffer<int> cb(5, 10);
    cb.pop_back();
    EXPECT_THROW(cb.rotate(4), std::out_of_range);
}

TEST(RotateTests, Rotate3) {
    CircularBuffer<int> cb(4);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4); // 1 (first) 2 3 4 (last)
    int old_front = cb.front();
    int old_back = cb.back();
    
    cb.rotate(2); // 3 4 (last) 1 (first) 2
    EXPECT_EQ(cb.front(), old_front);
    EXPECT_EQ(cb.back(), old_back);
}

TEST(RotateTests, Rotate4) {
    CircularBuffer<int> cb(4);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4);
    cb.push_back(5); // 5 (last) 2 (first) 3 4
    int old_front = cb.front();
    int old_back = cb.back();
    
    cb.rotate(2); // 4 5 (last) 2 (first) 3
    EXPECT_EQ(cb.front(), old_front);
    EXPECT_EQ(cb.back(), old_back);
}
