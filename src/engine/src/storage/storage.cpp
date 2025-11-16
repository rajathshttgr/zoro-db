#include "storage/storage.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Storage::Storage(const std::string& rootPath, const std::string& snapshotPath):root(rootPath), snapshot(snapshotPath){}

void Storage::init(){
    try {
        if (!fs::exists(root)) {
            fs::create_directories(root);
            std::cout << "Created storage dir: " << root << "\n";
        }

        if (!fs::exists(snapshot)) {
            fs::create_directories(snapshot);
            std::cout << "Created WAL dir: " << snapshot << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize storage: " << e.what() << "\n";
        throw;
    }

}