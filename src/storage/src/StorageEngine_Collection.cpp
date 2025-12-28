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

    bool StorageEngine::CreateCollection(const std::string& collection_name, int dimension, std::string distance){

    if(CollectionExists(collection_name)) return false;

    DistType dist_enum = DistTypeFromString(distance);
    std::string dist_str = DistTypeToString(dist_enum);

    // update catalog and get coll_id (call by reference update)
    int coll_id;
    if (!catalog_.AddCollection(collection_name, coll_id, dimension, distance))
        return false;

    // Append to WAL
    if (!wal_.log_create_collection(
            coll_id, collection_name, dimension, dist_enum)) {
        return false;
    }

    std::string path=collection_root_+"/"+collection_name;
    fs::create_directories(path);

    CollectionMeta meta(path);
    meta.InitDefault(dimension,dist_str,coll_id,collection_name);

    // catalog commit

    return true;
}

bool StorageEngine::DeleteCollection(const std::string& collection_name){

    int coll_id=catalog_.GetCollectionId(collection_name);

    if(coll_id==-1) return false;

    if (!wal_.log_delete_collection(coll_id)) {
        return false;
    }

    //this cannot be undone
    std::string path=collection_root_+"/"+collection_name;
    fs::remove_all(path);

    catalog_.RemoveCollection(collection_name);

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