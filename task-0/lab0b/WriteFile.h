#ifndef WRITEFILE_INCLUDE
#define WRITEFILE_INCLUDE

#include <string>
#include <fstream>

class WriteFile {
private:
    std::string file_name;
    std::ofstream file;

    void CheckFile();

public:
    WriteFile(std::string file_name);
    ~WriteFile();

    void Open();
    bool IsOpen();
    void CloseFile();
    void WriteLine(std::string line);
};

#endif
