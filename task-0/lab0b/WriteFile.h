#ifndef WRITEFILE_INCLUDE
#define WRITEFILE_INCLUDE

#include <string>
#include <fstream>
#include <vector>

class WriteFile {
private:
    std::string file_name;
    std::ofstream file;
    std::string delimiter = ",";

    void CheckFile();

public:
    WriteFile(std::string file_name);
    ~WriteFile();

    void Open();
    bool IsOpen();
    void CloseFile();
    void WriteLine(std::vector<std::string> elements);
};

#endif
