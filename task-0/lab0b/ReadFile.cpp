#include <stdexcept>
#include "ReadFile.h"

void ReadFile::CheckFile() {
    if (!IsOpen()) {
        throw std::runtime_error("File is not open.");
    }
}

ReadFile::ReadFile(std::string file_name) {
    this->file_name = file_name;
}

ReadFile::~ReadFile() {
    CloseFile();
}

void ReadFile::Open() {
    file.open(file_name);
    CheckFile();
}

bool ReadFile::IsOpen() {
    return file.is_open();
}

void ReadFile::CloseFile() {
    if (IsOpen()) {
        file.close();
    }
}

std::string ReadFile::ReadLine() {
    std::string line;
    std::getline(file, line);
    return line;
}

bool ReadFile::IsEmpty() {
    return file.eof();
}
