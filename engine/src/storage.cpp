#include "storage.hpp"
#include <filesystem>
#include <iostream>

namespace fs=std::filesystem;

namespace zoroStorage {
    bool Initialize(){
        if(!fs::exists(BASE_DIR)){
            fs::create_directories(BASE_DIR);
            std::cout << "[storage] Created " << BASE_DIR << "\n";
        }

        if(!fs::exists(COLLECTIONS_DIR)){
            fs::create_directories(COLLECTIONS_DIR);
            std::cout << "[storage] Created " << COLLECTIONS_DIR << "\n";
        }

        return true;
    }

    bool CreateCollectionDir(const std::string& name){
        fs::path collection_path=fs::path(COLLECTIONS_DIR) / name;

        if(!fs::exists(collection_path)){
            fs::create_directories(collection_path);
            return true;
        }
        return false;
    }
}