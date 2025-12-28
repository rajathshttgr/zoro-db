// last updated 28 Dec 2025, tests: passing

#include <gtest/gtest.h>
#include "../include/FileUtils.h"
#include <filesystem>

using namespace zoro::storage;

TEST(FileUtilsTest, WriteAndReadText) {
    std::string path = "test_file.txt";
    std::string content = "hello world";

    ASSERT_TRUE(FileUtils::WriteText(path, content));
    ASSERT_TRUE(FileUtils::Exists(path));

    auto read = FileUtils::ReadText(path);
    ASSERT_EQ(read, content);

    std::filesystem::remove(path);
}