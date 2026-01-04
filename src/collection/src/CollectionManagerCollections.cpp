#include "CollectionManager.h"

namespace zoro::core {

bool CollectionManager::CreateCollection(
    const std::string& name,
    int dimension,
    const std::string& distance
) {
    if (storage_->CollectionExists(name)) {
        return false;
    }
    return storage_->CreateCollection(name, dimension, distance);
}

bool CollectionManager::DeleteCollection(const std::string& name) {
    return storage_->DeleteCollection(name);
}

std::vector<zoro::storage::CollectionInfo>
CollectionManager::ListCollections() const {
    return storage_->ListCollections();
}

std::optional<zoro::storage::CollectionInfo>
CollectionManager::LoadCollection(const std::string& name) {
    if (!storage_->CollectionExists(name)) {
        return std::nullopt;
    }
    return storage_->GetCollectionInfo(name);
}

} // namespace zoro::core
