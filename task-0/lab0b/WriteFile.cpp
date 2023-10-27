#include <stdexcept>
#include "WriteFile.h"

void WriteFile::CheckFile() {
    if (!IsOpen()) {
        throw std::runtime_error("File is not open.");
    }
}

WriteFile::WriteFile(std::string file_name) {
    this->file_name = file_name;
}

WriteFile::~WriteFile() {
    CloseFile();
}

void WriteFile::Open() {
    file.open(file_name);
    CheckFile();
}

bool WriteFile::IsOpen() {
    return file.is_open();
}

void WriteFile::CloseFile() {
    if (IsOpen()) {
        file.close();
    }
}

void WriteFile::WriteLine(std::string line) {
    file << line << "\n";
}
