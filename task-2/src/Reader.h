#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include <fstream>
#include <string>
#include <set>
#include <list>

#define POS_NOT_SPECIFIED -1

class Reader {
private:
    std::string m_file_name;
    std::ifstream m_file_stream;
    std::ifstream::pos_type m_name_pos = POS_NOT_SPECIFIED;
    std::ifstream::pos_type m_rule_pos = POS_NOT_SPECIFIED;
    std::ifstream::pos_type m_coord_pos = POS_NOT_SPECIFIED;

    bool FormatIsCorrect();

    void SetBlockPositions();

public:
    Reader() {}

    /**
     * @brief Конструктор для жизни. Открывает файл.
     * @param file_name имя входного файла.
     * @throw std::runtime_error если ошибка при открытии или это файл не для игры.
    */
    Reader(std::string file_name);
    ~Reader();

    bool FileIsOpen();

    /**
     * @brief Открывает нужный файл.
     * @param file_name имя входного файла.
     * @throw std::runtime_error если ошибка при открытии или это файл не для игры.
    */
    void Open(std::string file_name);

    void Close();

    /**
     * @brief Чтение имени Вселенной.
     * @return Имя Вселенной.
     * @throw std::runtime_error если имя не было определено.
    */
    std::string ReadName();

    /**
     * @brief Чтение правила рождения.
     * @return Множество правил рождения для Вселенной из файла.
     * @throw std::runtime_error если правила не определены.
     * std::invalid_argument если правило не является действительным.
    */
    std::set<int> ReadBirthRule();

    /**
     * @brief Чтение правила выживания.
     * @return Множество правил выживания для Вселенной из файла.
     * @throw std::runtime_error если правила не определены.
     * std::invalid_argument если правило не является действительным.
    */
    std::set<int> ReadSurvivalRule();

    /**
     * @brief Чтение координат живых клеток.
     * @return Множество координат живых клеток.
     * @throw std::invalid_argument если координаты недействительны.
    */
    std::set<std::pair<int, int>> ReadCoords();
};

#endif
