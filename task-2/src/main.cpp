#include "Universe.h"
#include "ArgParser.h"
#include "CommandParser.h"
#include "Reader.h"
#include "Writer.h"
#include <iostream>

void GetArgValues(int argc, char** argv, std::string& in, std::string& out, std::string& iter) {
    ArgParser com_line(argc, argv);
    auto com_line_args = com_line.GetArgs();
    in = "";
    out = "";
    iter = "";

    for (const auto& arg : com_line_args) {
        if (arg.first == "-f") in = arg.second;
        else if (arg.first == "-o") out = arg.second;
        else if (arg.first == "-i") iter = arg.second;
    }
    if (in == "") in = "../files_for_game/default.lif";
}

void RunDefault(Universe& universe) {
    CommandParser com_parser;
    while (true) {
        std::string command;
        std::getline(std::cin, command);
        std::pair<std::string, std::string> parsed_command;
        try {
            parsed_command = com_parser.ParseCommand(command);
        } catch(std::invalid_argument exc) {
            std::cerr << exc.what();
            continue;
        }

        int ret_code = com_parser.ExecuteCommand(parsed_command, universe);
        if (ret_code == EXIT) return;
    }
}

void RunSilent(Universe& universe, std::string output_file, int iter) {
    for (int i = 0; i < iter; i++) {
        universe.Tick();
    }

    Writer writer(output_file);
    writer.Write(universe);
}

int main(int argc, char** argv) {
    std::string input_file, output_file, iter;
    GetArgValues(argc, argv, input_file, output_file, iter);

    Reader reader(input_file);
    std::string name;
    std::set<int> birth_rule, survival_rule;
    std::set<std::pair<int, int>> coords;

    try {
        name = reader.ReadName();
    } catch (std::runtime_error) {
        name = Universe::default_name;
    }
    try {
        birth_rule = reader.ReadBirthRule();
    } catch (std::runtime_error) {
        birth_rule = Universe::default_birth_rule;
    }
    catch (std::invalid_argument exc) {
        std::cerr << exc.what();
        return -1;
    }
    try {
        survival_rule = reader.ReadSurvivalRule();
    } catch (std::runtime_error) {
        survival_rule = Universe::default_survival_rule;
    }
    catch (std::invalid_argument exc) {
        std::cerr << exc.what();
        return -1;
    }
    try {
        coords = reader.ReadCoords();
    } catch (std::invalid_argument exc) {
        std::cerr << exc.what();
        return -1;
    }

    Universe universe(name, birth_rule, survival_rule, coords);

    if (output_file == "") { // обычный режим
        universe.PrintUniverse();
        RunDefault(universe);
    }
    else {
        RunSilent(universe, output_file, std::stoi(iter));
    }
}
