#include <gtest/gtest.h>
#include <fstream>
#include "../WriteFile.h"

TEST(FileWriterTest, FileIsOpen) {
    WriteFile writer("test.txt");
    EXPECT_EQ(false, writer.IsOpen());
}

TEST(FileWriterTest, WriteLine) {
    std::vector<std::string> input{"hello", "world"};
    std::string output = "hello,world";
    WriteFile writer("test.txt");
    writer.Open();
    writer.WriteLine(input);
    writer.CloseFile();

    std::ifstream file("test.txt");
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, output);
}
