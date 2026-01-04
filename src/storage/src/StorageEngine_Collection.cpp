#include "StorageEngine.h"
#include "Catalog.h"
#include "CollectionMeta.h"
#include "FileUtils.h"
#include "Distance_utils.h"
#include <filesystem>
#include <vector>
#include <cstdint>
#include <cstring> 

namespace fs=std::filesystem;

namespace zoro::storage {

    bool StorageEngine::CreateCollection(const std::string& collection_name, int dimension, std::string distance, int coll_id){

    std::string path=collection_root_+"/"+collection_name;
    fs::create_directories(path);

    CollectionMeta meta(path);
    meta.InitDefault(dimension, distance, coll_id, collection_name);

    return true;
}

bool StorageEngine::DeleteCollection(const std::string& collection_name){

    //this cannot be undone
    std::string path=collection_root_+"/"+collection_name;
    fs::remove_all(path);

    return true;
}

bool StorageEngine::CollectionExists(const std::string& name) const{
     return catalog_.CollectionExists(name);
}


std::optional<CollectionInfo> StorageEngine::GetCollectionInfo(const std::string& name) const{
    auto info_opt = catalog_.GetCollectionInfo(name);

    if (!info_opt) {
    return std::nullopt;
    }

    return info_opt;
}


std::vector<CollectionInfo> StorageEngine::ListCollections() const{
    
    auto collections = catalog_.ListCollections();
    
    return collections;
}
}