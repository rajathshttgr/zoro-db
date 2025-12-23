#include "StorageEngine.h"
#include "Catalog.h"
#include "CollectionMeta.h"
#include "FileUtils.h"
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


bool StorageEngine::CreateCollection(const std::string& name){

    std::vector<float> vec = {0.12f, 0.44f, 0.23f, 0.23f, 0.24f, 0.36f, 0.67f};
    std::vector<uint8_t> payload(sizeof(float) * vec.size());
    std::memcpy(payload.data(), vec.data(), payload.size());

    // Append to WAL
    if (wal_) {
        wal_->append(OpType::CREATE_COLLECTION, 100, payload);
    }

    if(CollectionExists(name)) return false;

    std::string path=collection_root_+"/"+name;
    fs::create_directories(path);

    Catalog catalog(root_path_);
    catalog.AddCollection(name, path);

    CollectionMeta meta(path);
    meta.InitDefault();

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