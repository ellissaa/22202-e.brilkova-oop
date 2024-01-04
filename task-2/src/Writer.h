#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

#include <fstream>
#include <string>
#include "Universe.h"

class Writer {
private:
    std::string m_file_name;
    std::ofstream m_file_stream;

public:
    Writer() {}

    /**
     * @brief Конструктор для записи в файл. Открывает файл.
     * @param file_name имя выходного файла.
     * @throw std::runtime_error если ошибка при открытии.
    */
    Writer(std::string file_name);
    ~Writer();

    bool FileIsOpen();

    /**
     * @brief Открывает выходной файл.
     * @param file_name имя вых. файла.
     * @throw std::runtime_error если ошибка при открытии.
    */
    void Open(std::string file_name);

    void Close();

    /**
     * @brief Записываем состояние Вселенной в файл.
     * @param universe Вселенная для записи.
     * @throw std::runtime_error если нет открытых файлов.
    */
    void Write(Universe& universe);
};

#endif
