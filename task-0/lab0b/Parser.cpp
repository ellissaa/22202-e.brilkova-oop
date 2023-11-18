#include "parser.h"

bool Parser::IsDelimiter(char symbol) {
    return !isalnum(symbol);
}

void Parser::AddWord(std::list <std::string> &words, std::string &word) {
    if (word != "") {
        words.insert(words.end(), word);
        word = "";
    }
}

std::list<std::string> Parser::Split(std::string line) {
    std::list<std::string> words;
    std::string word = "";

    for (auto symbol : line) {
        if (IsDelimiter(symbol)) {
            AddWord(words, word);
        }
        else {
            word += symbol;
        }
    }
    AddWord(words, word);

    return words;
}
