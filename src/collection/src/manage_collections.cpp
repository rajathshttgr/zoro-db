#include "CollectionManager.h"

namespace zoro::core {

bool CollectionManager::CreateCollection(
    const std::string& collection_name,
    int dimension,
    const std::string& distance,
    std::string& err
) {
    if (!storage_->CreateCollection(collection_name, dimension, distance, err)) {
        err = "Failed to create collection in storage [ER701]";
        return false;
    }
    return true;
}

bool CollectionManager::DeleteCollection(
    const std::string& collection_name, 
    std::string& err
) {
    if(!storage_->DeleteCollection(collection_name, err)) {
        err = "Failed to delete collection in storage [ER702]";
        return false;
    }

    return true;
}

} 

// orchetrate steps, let storage layer be dumb and independent 