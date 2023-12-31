#include <gtest/gtest.h>
#include "../WordMap.h"

using namespace std;

TEST(WordMapTest, AddWords1) {
    list<string> words = {"a", "b", "c", "d"};
    map<string, int> correct = {{"a", 1}, {"b", 1}, {"c", 1}, {"d", 1}};
    Map map;
    map.AddWords(words);
    EXPECT_EQ(map.GetWords(), correct);
}

TEST(WordMapTest, AddWords2) {
    list<string> words = {"a", "b", "a", "c"};
    map<string, int> correct = {{"a", 2}, {"b", 1}, {"c", 1}};
    Map map;
    map.AddWords(words);
    EXPECT_EQ(map.GetWords(), correct);
}

TEST(WordMapTest, AddWords3) {
    list<string> words = {};
    map<string, int> correct = {};
    Map map;
    map.AddWords(words);
    EXPECT_EQ(map.GetWords(), correct);
}

TEST(WordMapTest, GetSortredData1) {
    list<string> words = {"a", "b", "b"};
    list<pair<string, int>> correct = {{"b", 2}, {"a", 1}};
    Map map;
    map.AddWords(words);
    EXPECT_EQ(map.SortedList(), correct);
}

TEST(WordMapTest, GetSortredData2) {
    list<string> words = {"c", "b", "a"};
    list<pair<string, int>> correct = {{"a", 1}, {"b", 1}, {"c", 1}};
    Map map;
    map.AddWords(words);
    EXPECT_EQ(map.SortedList(), correct);
}

TEST(WordMapTest, GetSortredData3) {
    list<string> words = {"a", "c", "c", "b", "b"};
    list<pair<string, int>> correct = {{"b", 2}, {"c", 2}, {"a", 1}};
    Map map;
    map.AddWords(words);
    EXPECT_EQ(map.SortedList(), correct);
}
