#include "CollectionManager.h"
#include "../../storage/include/Distance_utils.h"

namespace zoro::core {

bool CollectionManager::LoadCollections(std::vector<zoro::utils::CollectionMetadata>& collections, std::string& err) {
    if(!storage_->LoadCollections(collections, err)) {
        err = "Failed Load all Collections [ER703]";
        return false;
    }

    return true;
}

bool CollectionManager::GetCollection(const std::string& name, zoro::utils::CollectionInfo& collection, std::string& err){
    if(!storage_->GetCollection(collection, name, err)) {
        if(err.empty()) {
           err = "Failed Load Collection Config [ER704]";
        }
        return false;
    }

    // add index config

    return true;
}


bool CollectionManager::CollectionExists(const std::string& name, std::string& err) {
    zoro::utils::CollectionInfo collection;
    if(!storage_->GetCollection(collection, name, err)) {
        err = "Failed Load Collection [ER705]";
        return false;
    }

    if(collection.status=="active"){
        return true;
    }

    // if status is pending or archived
    return false;
}



// DEPRECATED
std::vector<zoro::utils::CollectionInfo>
CollectionManager::ListCollections() const {
    return storage_->ListCollections();
}

std::optional<zoro::utils::CollectionInfo>
CollectionManager::LoadCollection(const std::string& name) {
    if (!storage_->CollectionExists(name)) {
        return std::nullopt;
    }
    return storage_->GetCollectionInfo(name);
}


} 
