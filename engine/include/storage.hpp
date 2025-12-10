#pragma once

#include <string>
#include <filesystem>

namespace zoroStorage {
    static const std::string BASE_DIR = ".zoro";
    static const std::string COLLECTIONS_DIR =  BASE_DIR + "/collections";

    bool Initialize();
    bool CreateCollectionDir(const std::string& name);
}