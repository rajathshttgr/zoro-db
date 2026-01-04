#include "StorageEngine.h"
#include <filesystem>

namespace fs=std::filesystem;

namespace zoro::storage {

StorageEngine::StorageEngine(const std::string& root_path)
    : root_path_(root_path), collection_root_(root_path+"/collections"), catalog_(root_path) {
    fs::create_directories(root_path_);
    fs::create_directories(collection_root_);
}

};