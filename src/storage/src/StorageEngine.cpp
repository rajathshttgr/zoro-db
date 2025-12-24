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

StorageEngine::StorageEngine(const std::string& root_path, zoro::wal::WALWriter* wal)
    : root_path_(root_path), collection_root_(root_path+"/collections"), wal_(wal) {
    fs::create_directories(root_path_);
    fs::create_directories(collection_root_);
}


bool StorageEngine::CreateCollection(const std::string& collection_name, int dimension, std::string distance){

    if(CollectionExists(collection_name)) return false;
    if(dimension==0) return false;

    DistType dist_enum = DistTypeFromString(distance);
    std::string dist_str = DistTypeToString(dist_enum);

    Catalog catalog(root_path_);

    // update catalog and get coll_id (call by reference update)
    int coll_id;
    if (!catalog.AddCollection(collection_name, coll_id))
        return false;

    // Append to WAL
    if (wal_) {
        wal_->append_create_collection(collection_name, dimension, dist_enum);
    }

    std::string path=collection_root_+"/"+collection_name;
    fs::create_directories(path);

    CollectionMeta meta(path);
    meta.InitDefault(dimension,dist_str,coll_id,collection_name);

    return true;
}

bool StorageEngine::DeleteCollection(const std::string& name){
    if(!CollectionExists(name)) return false;

    std::string path=collection_root_+"/"+name;
    fs::remove_all(path);

    Catalog catalog(root_path_);
    catalog.RemoveCollection(name);

    return true;
}


bool StorageEngine::CollectionExists(const std::string& name) const{
     return fs::exists(collection_root_+"/"+name);
}


std::optional<CollectionInfo> StorageEngine::GetCollectionInfo(const std::string& name) const{
    if(!CollectionExists(name)) return std::nullopt;

    CollectionInfo info;
    info.name=name;
    info.path=collection_root_+"/"+name;
    return info;
}


std::vector<CollectionInfo> StorageEngine::ListCollections() const{
    std::vector<CollectionInfo> collections;

    for(auto& entry: fs::directory_iterator(collection_root_)){
        if(entry.is_directory()){
            CollectionInfo info;
            info.name=entry.path().filename().string();
            info.path=entry.path().string();
            collections.push_back(info);
        }
    }
    return collections;
}

};