#include "storage/collection.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

namespace fs = std::filesystem;

Collection::Collection(const std::string& rootPath):storageRoot(rootPath){}

std::string Collection::Create(const std::string& collection_id) {

    std::string id = collection_id;
    fs::path colPath = fs::path(storageRoot) / id;

    int ext = 1;
    while (fs::exists(colPath)) {
        id = collection_id + "_" + std::to_string(ext);
        colPath = fs::path(storageRoot) / id;
        ext++;
    }

    // Create directory
    fs::create_directories(colPath);

    // Create config.json
    nlohmann::json cfg = {
        {"name", id},
        {"dimension", 128} 
    };

    std::ofstream(colPath / "config.json") << cfg.dump(4);

    // Create empty files
    std::ofstream(colPath / "vectors.bin");
    std::ofstream(colPath / "payload.bin");
    fs::create_directories(colPath / "wal");

    //std::cout << "Created new collection: " << id << "\n";

    return id;
}


std::string Collection::GetInfo(const std::string& collection_id){

    fs::path colPath = fs::path(storageRoot) / collection_id;

    if(fs::exists(colPath)){
        return "active";
    }

    return "unavailable";
}