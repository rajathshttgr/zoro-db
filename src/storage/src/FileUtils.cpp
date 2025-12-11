#include "../include/FileUtils.h"
#include <fstream>
#include <filesystem>

namespace fs=std::filesystem;

namespace zoro::storage{

bool FileUtils::Exists(const std::string& path){
    return fs::exists(path);
}

bool FileUtils::WriteText(const std::string& path, const std::string& content){
    std::ofstream out(path);
    if(!out) return false;
    out<<content;
    return true;
}

std::string FileUtils::ReadText(const std::string& path){
    std::ifstream in(path);

    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
   
}
}