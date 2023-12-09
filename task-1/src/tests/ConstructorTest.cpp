#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(ConstructorTests, Constr1_1) {
    int capacity = 5;
    CircularBuffer cb(capacity);
    EXPECT_EQ(cb.IsEmpty(), true);
    EXPECT_EQ(cb.capacity(), capacity);
}

TEST(ConstructorTests, Constr1_2) {
    int capacity = 0;
    CircularBuffer cb(capacity);
    EXPECT_EQ(cb.IsEmpty(), true);
    EXPECT_EQ(cb.IsFull(), true);
    EXPECT_EQ(cb.capacity(), capacity);
}

TEST(ConstructorTests, Constr2_1) {
    int capacity = 5;
    int item = 10;

    CircularBuffer cb(capacity, item);
    EXPECT_EQ(cb.IsFull(), true);
    EXPECT_EQ(cb.IsEmpty(), false);
    EXPECT_EQ(cb.capacity(), capacity);

    for (int i = 0; i < cb.size(); i++) {
        EXPECT_EQ(cb[i], item);
    }
}

TEST(ConstructorTests, CopyConstr) {
    int capacity = 5;
    int item = 10;

    CircularBuffer cb1(capacity, item);
    cb1[1] = 15;

    CircularBuffer cb2(cb1);
    EXPECT_EQ(cb1.size(), cb2.size());
    EXPECT_EQ(cb1.capacity(), cb2.capacity());

    for (int i = 0; i < cb1.size(); i++) {
        EXPECT_EQ(cb1[i], cb2[i]);
    }

    cb1[2] = 20;
    EXPECT_NE(cb1[2], cb2[2]);
}
