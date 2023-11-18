#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE

#include <string>
#include <list>

class Parser {
private:
    bool IsDelimiter(char symbol);
    void AddWord(std::list<std::string> &words, std::string &word);

public:
    std::list<std::string> Split(std::string line);
};

#endif
