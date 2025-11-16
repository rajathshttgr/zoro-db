#include "storage/collection.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

namespace fs = std::filesystem;

// to do: write logics as per requirements and replace existing
std::string Collection::Create(const std::string& name, const std::string& storageRoot) {
    // Generate a simple collection ID (improve later)
    std::string id = name;  

    fs::path colPath = fs::path(storageRoot) / id;

    if (fs::exists(colPath)) {
        throw std::runtime_error("Collection already exists!");
    }

    // Create directory
    fs::create_directories(colPath);

    // Create config.json
    nlohmann::json cfg = {
        {"name", name},
        {"id", id},
        {"dimension", 128} // default for now
    };

    std::ofstream(colPath / "config.json") << cfg.dump(4);

    // Create empty files
    std::ofstream(colPath / "vectors.bin");
    std::ofstream(colPath / "payload.bin");
    fs::create_directories(colPath / "wal");

    std::cout << "Created new collection: " << id << "\n";

    return id;
}
