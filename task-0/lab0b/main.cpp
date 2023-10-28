#include "Parser.h"
#include "ReadFile.h"
#include "WordMap.h"
#include "WriteFile.h"
#include <iostream>

#define ERROR -1

int main(int argc, char** argv) {
    if (argc != 3) {
        std:cerr << "Bad number of arguments, 3 expected\n";
        return ERROR;
    }

    ReadFile reader(argv[1]);
    try {
        reader.Open();
    }
    catch (std::runtime_error &exception) {
        std::cerr << exception.what() << "\n";
        return ERROR;
    }

    Parser parser;
    Map word_map;

    while (!reader.IsEmpty()) {
        std::string line = reader.ReadLine();
        std::list<std::string> split_line = parser.Split(line);
        word_map.AddWords(split_line);
    }
    reader.CloseFile();

    std::list<std::pair<std::string, int>> sorted_list = word_map.SortedList();

    WriteFile writer(argv[2]);
    try {
        writer.Open();
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what() << "\n";
        return ERROR;
    }

    std::vector<std::string> exit_line = {'Word', "Quantity", "Frequency"};
    for (const auto &entry : sorted_list) {
        double frequency = (double)entry.second / word_map.Count();
        std::vector<std::string> exit_line = {entry.first, to_string(entry.second), to_string(frequency)};
        writer.WriteLine(exit_line);
    }
    writer.CloseFile();
}
