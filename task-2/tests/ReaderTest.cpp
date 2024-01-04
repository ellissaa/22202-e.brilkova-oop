#include <gtest/gtest.h>
#include "../src/Reader.h"

TEST(ReaderTests, NoFile) {
    EXPECT_THROW(Reader r("no such file"), std::runtime_error);
}

TEST(ReaderTests, OpenInvalidFormat) {
    Reader r;
    EXPECT_THROW(r.Open("../test_files/invalid_format.lif"), std::runtime_error);
}

TEST(ReaderTests, ReadCorrect) {
    Reader r("../test_files/correct.lif");
    std::string name = "universe";
    std::set<int> birth_rule{1, 2 ,3};
    std::set<int> survival_rule{4, 5, 6};
    std::set<std::pair<int, int>> coords{{1, 0}, {2, 5}, {4, -3}};
    
    EXPECT_EQ(r.ReadName(), name);
    EXPECT_EQ(r.ReadBirthRule(), birth_rule);
    EXPECT_EQ(r.ReadSurvivalRule(), survival_rule);
    EXPECT_EQ(r.ReadCoords(), coords);
}

TEST(ReaderTests, NoName) {
    Reader r("../test_files/no_name.lif");
    std::set<int> birth_rule{1, 2 ,3};
    std::set<int> survival_rule{4, 5, 6};
    std::set<std::pair<int, int>> coords{{1, 0}, {9, 5}, {4, -6}};

    EXPECT_THROW(r.ReadName(), std::runtime_error);
    EXPECT_EQ(r.ReadBirthRule(), birth_rule);
    EXPECT_EQ(r.ReadSurvivalRule(), survival_rule);
    EXPECT_EQ(r.ReadCoords(), coords);
}

TEST(ReaderTests, OnlyCoords) {
    Reader r("../test_files/only_coords.lif");
    std::set<std::pair<int, int>> coords{{1, 0}, {9, 5}, {4, -6}};

    EXPECT_THROW(r.ReadName(), std::runtime_error);
    EXPECT_THROW(r.ReadBirthRule(), std::runtime_error);
    EXPECT_THROW(r.ReadSurvivalRule(), std::runtime_error);
    EXPECT_EQ(r.ReadCoords(), coords);
}

TEST(ReaderTests, NoBirth) {
    Reader r("../test_files/no_birth.lif");
    std::set<int> survival_rule{4, 5};
    EXPECT_THROW(r.ReadBirthRule(), std::runtime_error);
    EXPECT_EQ(r.ReadSurvivalRule(), survival_rule);
}

TEST(ReaderTests, NoSurvival) {
    Reader r("../test_files/no_survival.lif");
    std::set<int> birth_rule{1, 2};
    EXPECT_THROW(r.ReadSurvivalRule(), std::runtime_error);
    EXPECT_EQ(r.ReadBirthRule(), birth_rule);
}

TEST(ReaderTests, EmptyRule) {
    Reader r("../test_files/empty_rule.lif");
    std::set<int> birth_rule{};
    std::set<int> survival_rule{};
    EXPECT_EQ(r.ReadBirthRule(), birth_rule);
    EXPECT_EQ(r.ReadSurvivalRule(), survival_rule);
}

TEST(ReaderTests, InvalidRule) {
    Reader r("../test_files/invalid_rule.lif");
    EXPECT_THROW(r.ReadBirthRule(), std::invalid_argument);
    EXPECT_THROW(r.ReadSurvivalRule(), std::invalid_argument);
}

TEST(ReaderTests, InvalidCoords1) {
    Reader r("../test_files/invalid_coords1.lif");
    EXPECT_THROW(r.ReadCoords(), std::invalid_argument);
}

TEST(ReaderTests, InvalidCoords2) {
    Reader r("../test_files/invalid_coords2.lif");
    EXPECT_THROW(r.ReadCoords(), std::invalid_argument);
}

TEST(ReaderTests, InvalidCoords3) {
    Reader r("../test_files/invalid_coords3.lif");
    EXPECT_THROW(r.ReadCoords(), std::invalid_argument);
}

TEST(ReaderTests, InvalidCoords4) {
    Reader r("../test_files/invalid_coords4.lif");
    EXPECT_THROW(r.ReadCoords(), std::invalid_argument);
}

TEST(ReaderTests, NoCoords) {
    Reader r("../test_files/no_coords.lif");
    std::set<std::pair<int, int>> coords{};
    EXPECT_EQ(r.ReadCoords(), coords);
}
