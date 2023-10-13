#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <utility>

enum ExitCodes {
    BAD_NUMBER_OF_ARGS = -1,
    BAD_FILE,
};

bool Compare(std::pair<std::string, int> first, std::pair<std::string, int> second) {
    if (first.second > second.second) {
        return true;
    }
    else return false;
}

void ReadFile(std::ifstream *file, std::map<std::string, int> *words, int *counter) {
    while (!(*file).eof()) {
        std::string line;
        std::getline((*file), line);

        std::string::iterator line_iter;
        std::string word = "";

        for (line_iter = line.begin(); line_iter != line.end(); line_iter++) {
            char symbol = *line_iter;
            if (isalnum(symbol)) {
                word += symbol;
            }
            else if (word != "") {
                *counter += 1;
                if ((*words).count(word) == 1) { //значит слово добавлено
                    (*words)[word] += 1; //вернули значение по ключу и увеличили на 1
                }
                else {
                    (*words)[word] = 1; //(word, 1) добавили в мапу
                }
                word = "";
            }
        }
        if (word != "") {
            *counter += 1;
            if ((*words).count(word) == 1) { //значит слово добавлено
                (*words)[word] += 1; //вернули значение по ключу и увеличили на 1
            }
            else {
                (*words)[word] = 1; //(word, 1) добавили в мапу
            }
            word = "";
        }
    }
}

void WriteOutFile(std::ofstream *out_file, std::list<std::pair<std::string, int>> *list, int counter) {
    (*out_file) << "Word, Quantity, Frequency\n";

    std::list<std::pair<std::string, int>>::iterator list_iter;
    for (list_iter = (*list).begin(); list_iter != (*list).end(); list_iter++) {
        (*out_file) << (*list_iter).first << ", " << (*list_iter).second << ", " << (double)(*list_iter).second/counter << "%\n";
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Bad number of arguments.\n";
        return BAD_NUMBER_OF_ARGS;
    }

    std::string input_file = argv[1];
    std::ifstream file (input_file); //открываем файл и создаем файловый поток (посл-ть символов)
    if (!file.is_open()) {
        std::cerr << "Bad input file.\n";
        return BAD_FILE;
    }

    int counter = 0;
    std::map<std::string, int> words;

    ReadFile(&file, &words, &counter);
    file.close();

    std::list<std::pair<std::string, int>> list(words.begin(), words.end()); //создали список, элементы в котором
    //это пары(ключ (слово), значение (кол-во)), сразу скопировали сюда мапу
    list.sort(Compare);

    std::string output_file = argv[2];
    std::ofstream out_file (output_file); //открываем файл и создаем файловый поток (посл-ть символов)
    if (!out_file.is_open()) {
        std::cerr << "Bad output file.\n";
        return BAD_FILE;
    }

    WriteOutFile(&out_file, &list, counter);
    out_file.close();
}
