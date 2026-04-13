#include "StorageEngine.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
#include <execution>
#include <thread>
#include <atomic>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace zoro::storage {

// detached thread to delete directories asynchronously
void delete_async(const fs::path& dir) {
    std::thread([dir]() {
        try {
            fs::remove_all(dir);
        } catch (...) {
            // TODO: logging system
        }
    }).detach();
}

bool StorageEngine::LoadCollections(
    std::vector<zoro::utils::CollectionMetadata>& collections,
    std::string& err) {

    std::vector<fs::path> dirs;
    dirs.reserve(256);

    std::atomic<bool> had_error = false;

    // Collect directories
    for (const auto& entry : fs::directory_iterator(collection_root_)) {
        if (entry.is_directory()) {
            dirs.push_back(entry.path());
        }
    }

    // Indexed mapping for parallel safety
    std::vector<std::pair<size_t, fs::path>> indexed_dirs;
    indexed_dirs.reserve(dirs.size());

    for (size_t i = 0; i < dirs.size(); ++i) {
        indexed_dirs.emplace_back(i, dirs[i]);
    }

    // Temporary result buffer
    std::vector<zoro::utils::CollectionMetadata> temp_collections(dirs.size());

    // Parallel processing
    std::for_each(std::execution::par,
        indexed_dirs.begin(), indexed_dirs.end(),
        [&](const auto& p) {

            size_t idx = p.first;
            const fs::path& dir = p.second;

            const std::string name = dir.filename().string();

            // delete temp directories (partial collections from crashes)
            if (name.rfind("__temp", 0) == 0) {
                delete_async(dir);
                return;
            }

            const fs::path metapath = dir / "meta.json";

            // missing meta file - delete (ideally don't happen)
            if (!fs::exists(metapath)) {
                delete_async(dir);
                return;
            }

            std::ifstream in(metapath);

            // If exists but can't open → system issue
            if (!in) {
                err = "storage error: unable to open metadata file for collection " + name;
                had_error = true;
                return;
            }

            try {
                json j;
                in >> j;

                zoro::utils::CollectionMetadata c{
                    j.value("coll_name", ""),
                    j.value("dimensions", 0),
                    j.value("distance", ""),
                    j.value("status", "")
                };

                temp_collections[idx] = std::move(c);

            } catch (...) {
                err = "storage error: something went wrong while parsing metadata for collection " + name;
                had_error = true;
            }
        }
    );

    if (had_error) {
        // err = "Unexpected error occurred during collections loading";
        return false;
    }

    collections = std::move(temp_collections);

    return true;
}

} 