#include "vectordb/vector_db.hpp"
#include <filesystem>
#include <chrono>
#include <string>
#include <sstream>

namespace fs=std::filesystem;

namespace vectordb{

VectorDB::VectorDB(const std::string& storagePath):_storagePath(storagePath){
    _storage=std::make_unique<storageManager>(_storagePath);
    _collectionManager = std::make_unique<CollectionManager>(_storagePath);
}

bool VectorDB::init(){
    if(!_storage->ensureStorageDirectory()){
        return false;
    }

    // create collections folder
    fs::create_directories(_storagePath+"/collections");

    _dbConfig.collections.clear();

    auto now = std::chrono::system_clock::now();
    auto tt = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
    _dbConfig.last_updated = ss.str();

    return _storage->saveDBConfig(_dbConfig);
}


bool VectorDB::load() {
    if (!_storage->ensureStorageDirectory()) {
        return false;
    }

    if (!loadDBConfig()) {
        return false;
    }

    _collectionManager->setCollections(_dbConfig.collections);

    return true;
}

bool VectorDB::loadDBConfig() {
    if (!_storage->loadDBConfig(_dbConfig)) {
        return false;
    }
    return true;
}

bool VectorDB::saveDBConfig() {
    return _storage->saveDBConfig(_dbConfig);
}

}