#include "CollectionManager.h"
#include "../../storage/include/Distance_utils.h"

namespace zoro::core {

bool CollectionManager::CreateCollection(
    const std::string& collection_name,
    int dimension,
    const std::string& distance
) {
    if (storage_->CollectionExists(collection_name)) {
        return false;
    }

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

    return storage_->CreateCollection(collection_name, dimension, dist_str, coll_id);
}

bool CollectionManager::DeleteCollection(const std::string& collection_name) {

    int coll_id=catalog_.GetCollectionId(collection_name);

    if(coll_id==-1) return false;

    if (!wal_.log_delete_collection(coll_id)) {
        return false;
    }

    bool deleteSucess = storage_->DeleteCollection(collection_name);

    if(!deleteSucess) return false;

    catalog_.RemoveCollection(collection_name);
    return true;
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
