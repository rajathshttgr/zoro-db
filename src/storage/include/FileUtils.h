#pragma once
#include <string>
#include <fstream>

namespace zoro::storage{

class FileUtils {
public:
    static bool Exists(const std::string& path);
    static bool CreateFileIfNotExists(const std::string& path);
    static bool WriteText(const std::string& path, const std::string& content);
    static bool WriteBinary(const std::string& path, const char* data, size_t size);
    static std::string ReadText(const std::string& path);
};
}