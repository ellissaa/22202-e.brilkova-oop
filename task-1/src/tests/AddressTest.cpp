#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(AddressTests, IndexAccess1) {
    CircularBuffer cb(5, 10);
    cb[1] = 15;
    EXPECT_EQ(cb[1], 15);
    EXPECT_EQ(cb[3], 10);
}

TEST(AddressTests, IndexAccess2) {
    CircularBuffer cb(5, 10);
    EXPECT_NO_THROW(cb[100]);
    EXPECT_NO_THROW(cb[-100]);
}

TEST(AddressTests, AtMethod1) {
    CircularBuffer cb(5, 10);
    cb.at(1) = 15;
    EXPECT_EQ(cb.at(3), 10);
    EXPECT_EQ(cb.at(1), 15);
}

TEST(AddressTests, AtMethod2) {
    CircularBuffer cb(5, 10);
    EXPECT_THROW(cb.at(100), std::out_of_range);
    EXPECT_THROW(cb.at(-100), std::out_of_range);
}

TEST(AddressTests, AtMethod3) {
    CircularBuffer cb(5, 10);
    EXPECT_THROW(cb.at(5), std::out_of_range);
}

TEST(AddressTests, AtMethod4) {
    CircularBuffer cb(5);
    EXPECT_THROW(cb.at(0), std::out_of_range);
}

TEST(AddressTests, FrontMethod1) {
    CircularBuffer cb(5, 10);
    EXPECT_EQ(cb.front(), 10);
}

TEST(AddressTests, FrontMethod2) {
    CircularBuffer cb(5, 10);
    cb.front() = 15;
    EXPECT_EQ(cb.front(), 15);
}

TEST(AddressTests, FrontMethod3) {
    CircularBuffer cb(5);
    EXPECT_THROW(cb.front(), std::out_of_range);
}

TEST(AddressTests, BackMethod1) {
    CircularBuffer cb(5, 10);
    EXPECT_EQ(cb.back(), 10);
}

TEST(AddressTests, BackMethod2) {
    CircularBuffer cb(5, 10);
    cb.back() = 15;
    EXPECT_EQ(cb.back(), 15);
}

TEST(AddressTests, BackMethod3) {
    CircularBuffer cb(5);
    EXPECT_THROW(cb.back(), std::out_of_range);
}
