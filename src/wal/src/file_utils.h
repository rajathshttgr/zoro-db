#pragma once

#include <filesystem>

bool file_exists(const std::string& path){
    return std::filesystem::exists(path);
}

bool create_directory(const std::string& path){
    if(file_exists(path)){
        return true;
    }
    return std::filesystem::create_directories(path);
}

