#include "StorageEngine.h"
#include "Catalog.h"
#include "CollectionMeta.h"
#include "FileUtils.h"
#include "Distance_utils.h"
#include <filesystem>
#include <vector>
#include <cstdint>
#include <cstring> 
#include <fstream>

namespace fs=std::filesystem;
using json = nlohmann::json;

namespace zoro::storage {

bool StorageEngine::GetCollection(zoro::utils::CollectionInfo& collection, const std::string& collection_name, std::string& err){
    const fs::path metapath = fs::path(collection_root_)/collection_name/"meta.json";
    if (!fs::exists(metapath)) {
        err = "storage error: metadata file not found";
        return false;
    }
    std::ifstream in(metapath);
    if (!in) {
        err = "storage error: unable to open metadata file";
        return false;
    }

    try {
        json j;
        in >> j;

        zoro::utils::CollectionInfo c{
            j.value("coll_name", ""),
            j.value("dimensions", 0),
            j.value("distance", ""),
            j.value("status", "")
        };

        collection = std::move(c);

    } catch (...) {
        err = "storage error: something went wrong";
        return false;
    }

    return true;
}

// deprecated
bool StorageEngine::CollectionExists(const std::string& name) {
    zoro::utils::CollectionInfo collection;
    std::string err;
    if(!this->GetCollection(collection, name, err)){
        return false;
    }
    return collection.status=="active";
    // earlier this function was depending on catalog
    // catalog_.CollectionExists(name, err);
}

// deprecated - no longer system depends on catalog
std::optional<zoro::utils::CollectionInfo> StorageEngine::GetCollectionInfo(const std::string& name) const{
    auto info_opt = catalog_.GetCollectionInfo(name);

    if (!info_opt) {
    return std::nullopt;
    }

    return info_opt;
}

// deprecated - no longer system depends on catalog
std::vector<zoro::utils::CollectionInfo> StorageEngine::ListCollections() const{
    
    auto collections = catalog_.ListCollections();
    
    return collections;
}
}