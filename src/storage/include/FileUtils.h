#pragma once
#include <string>

namespace zoro::storage{

class FileUtils {
public:
    static bool Exists(const std::string& path);
    static bool WriteText(const std::string& path, const std::string& content);
    static std::string ReadText(const std::string& path);
};
}