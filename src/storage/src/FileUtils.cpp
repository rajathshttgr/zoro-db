#include "FileUtils.h"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs=std::filesystem;

namespace zoro::storage{

bool FileUtils::Exists(const std::string& path){
    return fs::exists(path);
}

bool FileUtils::CreateFileIfNotExists(const std::string& path) {
    try {
        fs::path filePath(path);

        if (filePath.has_parent_path()) {
            fs::create_directories(filePath.parent_path());
        }

        if (!fs::exists(filePath)) {
            std::ofstream ofs(filePath);
            if (!ofs) {
                return false;
            }
        }

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool FileUtils::WriteText(const std::string& path, const std::string& content){
    std::ofstream out(path);
    if(!out) return false;
    out<<content;
    return true;
}

bool FileUtils::WriteBinary(const std::string& path, const char* data, size_t size)
{
    std::ofstream ofs(path, std::ios::binary | std::ios::app);
    if (!ofs) return false;

    ofs.write(data, size);
    return ofs.good();
}

std::string FileUtils::ReadText(const std::string& path){
    std::ifstream in(path);

    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
   
}
}