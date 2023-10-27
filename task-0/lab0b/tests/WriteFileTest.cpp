#include <gtest/gtest.h>
#include <fstream>
#include "../WriteFile.h"

TEST(FileWriterTest, FileIsOpen) {
    WriteFile writer("test.txt");
    EXPECT_EQ(false, writer.IsOpen());
}

TEST(FileWriterTest, WriteLine) {
    WriteFile writer("test.txt");
    writer.Open();
    writer.WriteLine("testing");
    writer.CloseFile();

    std::ifstream file("test.txt");
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "testing");
}
