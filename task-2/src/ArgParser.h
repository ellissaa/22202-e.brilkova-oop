#ifndef ARG_PARSER_H_INCLUDED
#define ARG_PARSER_H_INCLUDED

#include <string>
#include <set>
#include <map>

/// @brief Класс для обработки параметров командной строки
class ArgParser {
private:
    static std::set<std::string> valid_args; // корректные параметры
    std::map<std::string, std::string> arg_map;

    void ParseArgs(int argc, char** argv);

    bool SetOfArgsIsValid(); // true если данная комбинация параметров корректна.

public:
    /**
     * @brief Читает параметры командной строки, проверяет их корректность и
     * сохраняет их значения.
     * @param argc количество параметров.
     * @param argv параметры командной строки.
     * @exception std::invalid_argument если параметры некорректны.
    */
    ArgParser(int argc, char** argv);

    std::map<std::string, std::string> GetArgs(); // Возвращает мапу параметров командной строки.
};

#endif
