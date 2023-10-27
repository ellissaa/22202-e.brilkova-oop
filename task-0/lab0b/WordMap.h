#ifndef WORDMAP_INCLUDE
#define WORDMAP_INCLUDE

#include <string>
#include <list>
#include <map>
#include <utility>

using namespace std;

class Map {
private:
    map<string, int> exit_list;
    int counter = 0;

    static bool Compare (pair<string, int> first_p, pair<string, int> second_p);

public:
    void AddWord(string word);
    void AddWords(list<string> words);

    map<string, int> &GetWords();

    int Count();

    list<pair<string, int>> SortedList();
};

#endif
