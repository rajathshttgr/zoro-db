#include "CollectionManager.h"

namespace zoro::core {

bool CollectionManager::UpsertPoints(
    const std::string& collection_name,
    const std::vector<int>& point_id,
    const std::vector<std::vector<float>>& vectors,
    const std::vector<nlohmann::json>& payload
) {
    const size_t count = point_id.size();

    if (count == 0 ||
        vectors.size() != count ||
        payload.size() != count) {
        return false;
    }

    if (!storage_->CollectionExists(collection_name)) {
        return false;
    }

    int coll_id=catalog_.GetCollectionId(collection_name);

    // Append to WAL 
    for (size_t i = 0; i < count; ++i) {
        if (!wal_.log_upsert_point(coll_id, point_id[i], vectors[i], payload[i])) {
            return false;
        }
    }

    // Disk write
    for (size_t i = 0; i < count; ++i) {
        if (!storage_->UpsertPoints(
                collection_name,
                point_id[i],
                vectors[i],
                payload[i])) {
            return false;
        }
    }

    return true;
}

bool CollectionManager::DeletePoints(
    const std::string& collection_name,
    const std::vector<int> point_id
) {

    if (!storage_->CollectionExists(collection_name)) {
        return false;
    }

    int coll_id=catalog_.GetCollectionId(collection_name);

    // Append to WAL
    for (int id : point_id) {
        if (!wal_.log_delete_point(coll_id, id)) {
            return false;
        }
    }
    

    // disk write
    for (int id : point_id) {
        if (!storage_->DeletePoints(collection_name, id)) {
            return false;
        }
    }
    return true;
}

int CollectionManager::CountPoints(const std::string& coll_name) {
    if (!storage_->CollectionExists(coll_name)) {
        return -1;
    }
    return storage_->CountPoints(coll_name);
}

} // namespace zoro::core
