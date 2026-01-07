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

    // In-memory index update
    EnsureIndex(collection_name);

    for (size_t i = 0; i < count; ++i) {
        runtimes_[collection_name].index->add(vectors[i].data(), point_id[i]);
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


    // In Memory index update
    EnsureIndex(collection_name);
    for (int id : point_id) {
        runtimes_[collection_name].index->remove(id);
    }

    return true;
}

int CollectionManager::CountPoints(const std::string& coll_name) {
    if (!storage_->CollectionExists(coll_name)) {
        return -1;
    }
    return storage_->CountPoints(coll_name);
}



std::vector<zoro::storage::SearchPointInfo>
CollectionManager::SearchPointByVector(
    const std::string& coll_name,
    const std::vector<float>& query_vector,
    int k
) {
    std::vector<zoro::storage::SearchPointInfo> output;

    if (!storage_->CollectionExists(coll_name)) {
        return output;
    }

    EnsureIndex(coll_name);

    auto result = runtimes_[coll_name].index->search(query_vector.data(), k);

    for (size_t i = 0; i < result.point_ids.size(); ++i) {
        int point_id = static_cast<int>(result.point_ids[i]);

        std::string err;
        auto meta = storage_->GetMetadataByPointId(coll_name, point_id, err);
        if (!meta.has_value()) {
            continue; // skip missing/deleted points
        }

        zoro::storage::SearchPointInfo info;
        info.point_id = point_id;

        // score strategy (simple version)
        info.score = static_cast<int>(1000 / (1.0f + result.distances[i]));

        info.payload = meta->payload;

        output.push_back(std::move(info));
    }

    return output;
}


} // namespace zoro::core


