#ifndef READFILE_INCLUDE
#define READFILE_INCLUDE

#include <string>
#include <fstream>

class ReadFile {
private:
    std::string file_name;
    std::ifstream file;

    void CheckFile();

public:
    ReadFile(std::string file_name);
    ~ReadFile();

    void Open();
    bool IsOpen();
    void CloseFile();

    std::string ReadLine();
    bool IsEmpty();
};

#endif
