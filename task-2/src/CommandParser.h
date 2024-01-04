#ifndef COMMAND_HANDLER_H_INCLUDED
#define COMMAND_HANDLER_H_INCLUDED

#include <string>
#include <set>
#include <utility>
#include "Universe.h"

#define CONTINUE 0
#define EXIT 1

class CommandParser {
private:
    static std::set<std::string> m_valid_commands;
    static std::string m_help_message;

    void Dump(std::string o_file, Universe& universe);
    void Tick(int num_of_ticks, Universe& universe);
    void Exit();
    void Help();

public:
    /**
     * @brief Анализирует команду и разделяет ее на имя и значение.
     * @return пара имя команды, значение команды. Если команда не имеет значения, записывается пустая строка.
     * @exception std::invalid_argument если команда или ее значение неверные.
    */
    std::pair<std::string, std::string> ParseCommand(std::string command);

    /**
     * @brief Применяет данную команду ко Вселенной.
     * @param command имя команды и значение команды. Его необходимо вернуть
     * методом ParseCommand. Иначе поведение неопределено.
     * @param universe Вселенная, на кот. нужно ссылаться.
     * @return Либо CONTINUE (в этом случае игра продолжается), либо EXIT (игра должна быть закончена).
    */
    int ExecuteCommand(std::pair<std::string, std::string> command, Universe& universe);
};

#endif
