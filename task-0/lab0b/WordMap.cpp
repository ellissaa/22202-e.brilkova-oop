#include "WordMap.h"

bool Map::Compare(pair<string, int> first_p, pair<string, int> second_p) {
    return first_p.second > second_p.second || (first_p.second == second_p.second && first_p.first < second_p.first);
}

void Map::AddWord(string word) {
    if (exit_list.count(word) > 0) {
        exit_list[word]++;
    }
    else {
        exit_list[word] = 1;
    }
    counter++;
}

void Map::AddWords(list <string> words) {
    for (const auto &word : words) {
        AddWord(word);
    }
}

map<string, int> &Map::GetWords() {
    return exit_list;
}

int Map::Count() {
    return counter;
}

list<pair<string, int>> Map::SortedList() {
    list<pair<string, int>> sorted_list(exit_list.begin(), exit_list.end());
    sorted_list.sort(Compare);
    return sorted_list;
}
