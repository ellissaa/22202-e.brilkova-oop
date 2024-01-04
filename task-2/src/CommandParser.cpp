#include <iostream>
#include "CommandParser.h"
#include "Writer.h"

/// @return true, если num_of_ticks представляет собой допустимое положительное целое число.
static bool TickIsValid(std::string num_of_ticks) {
    for (const auto& ch : num_of_ticks) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    if (std::stoi(num_of_ticks) <= 0) return false;
    return true;
}

std::set<std::string> CommandParser::m_valid_commands {
        "dump", "tick", "t", "exit", "help"};

std::string CommandParser::m_help_message = "Game of Life\n"
                                             "Available commands:\n"
                                             "dump <filename> - save universe to file;\n"
                                             "tick (t for short) <n=1> - calculate n (default 1) iterations and print "
                                             "the universe;\n"
                                             "exit - exit the game;\n"
                                             "help - print this help message.";

void CommandParser::Dump(std::string o_file, Universe& universe) {
    try {
        Writer file_writer(o_file);
        file_writer.Write(universe);
        std::cout << "Universe saved to " << o_file << ".\n";
    } catch (std::runtime_error exc) {
        std::cout << exc.what() << "\n";
    }
}

void CommandParser::Tick(int num_of_ticks, Universe& universe) {
    for (int i = 0; i < num_of_ticks; i++) {
        universe.Tick();
    }
    universe.PrintUniverse();
}

void CommandParser::Exit() {
    std::cout << "Exiting the game\n";
}

void CommandParser::Help() {
    std::cout << m_help_message << "\n";
}

std::pair<std::string, std::string> CommandParser::ParseCommand(std::string command) {
    std::string com_name, com_arg = "";
    auto space_pos = command.find(' ');
    if (space_pos == std::string::npos) {
        com_name = command;
    }
    else {
        com_name = command.substr(0, space_pos);
        com_arg = command.substr(space_pos + 1);
    }

    if (!m_valid_commands.contains(com_name)) {
        std::string err_msg = "Unknown command: " + com_name + ".\n";
        Help();
        throw std::invalid_argument(err_msg);
    }

    if (com_name == "t") com_name = "tick";
    if (com_name == "tick") {
        if (com_arg == "") {
            com_arg = "1";
        }
        else if (!TickIsValid(com_arg)) {
            throw std::invalid_argument(
                    "Number of ticks must be a positive integer.");
        }
    }

    if (com_name == "dump" && com_arg == "") {
        throw std::invalid_argument("No output file provided.");
    }
    return {com_name, com_arg};
}

int CommandParser::ExecuteCommand(std::pair<std::string, std::string> command, Universe& universe) {
    std::string com_name = command.first;
    if (com_name == "dump") {
        Dump(command.second, universe);
        return CONTINUE;
    }
    else if (com_name == "tick") {
        Tick(std::stoi(command.second), universe);
        return CONTINUE;
    }
    else if (com_name == "exit") {
        Exit();
        return EXIT;
    }
    else {
        Help();
        return CONTINUE;
    }
}
