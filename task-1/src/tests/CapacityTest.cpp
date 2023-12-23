#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(CapacityTests, SetCapacity1) {
    CircularBuffer cb;
    cb.set_capacity(10);
    EXPECT_EQ(cb.capacity(), 10);
}

TEST(CapacityTests, SetCapacity2) {
    CircularBuffer cb(3, 10);
    cb.set_capacity(10);
    EXPECT_EQ(cb.capacity(), 10);
    EXPECT_EQ(cb.size(), 3);

    for (int i = 0; i < cb.size(); i++) {
        EXPECT_EQ(cb[i], 10);
    }
}

TEST(CapacityTests, SetCapacity3) {
    CircularBuffer cb(5, 10);
    cb.set_capacity(3);
    EXPECT_EQ(cb.capacity(), 3);
    EXPECT_EQ(cb.size(), 3);

    for (int i = 0; i < cb.size(); i++) {
        EXPECT_EQ(cb[i], 10);
    }
}

TEST(CapacityTests, SetCapacity4) {
    CircularBuffer cb(3, 10);
    cb.set_capacity(0);
    EXPECT_EQ(cb.capacity(), 0);
    EXPECT_EQ(cb.size(), 0);
}

TEST(CapacityTests, Resize1) {
    CircularBuffer cb(3, 10);
    int old_size = cb.size();

    cb.resize(5, 15);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 5);

    for (int i = 0; i < old_size; i++) {
        EXPECT_EQ(cb[i], 10);
    }
    for (int i = old_size; i < cb.size(); i++) {
        EXPECT_EQ(cb[i], 15);
    }
}

TEST(CapacityTests, Resize2) {
    CircularBuffer cb(5, 10);

    cb.resize(3, 15);
    EXPECT_EQ(cb.capacity(), 3);
    EXPECT_EQ(cb.size(), 3);

    for (int i = 0; i < cb.size(); i++) {
        EXPECT_EQ(cb[i], 10);
    }
}
