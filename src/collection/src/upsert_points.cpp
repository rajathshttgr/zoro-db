#include <thread>
#include "CollectionManager.h"
#include "../../storage/include/Distance_utils.h"
#include "../../wal/include/wal_writer.h"

namespace zoro::core {

void CollectionManager::UpsertAsyncOperation(const std::string& collection_name,
    const std::vector<int>& point_id,
    const std::vector<std::vector<float>>& vectors,
    const std::vector<nlohmann::json>& payload,
    const int& count,
    int& operation_id){
    // Disk write
    for (size_t i = 0; i < count; ++i) {
        if (!storage_->UpsertPoints(
                collection_name,
                point_id[i],
                vectors[i],
                payload[i])) {
            continue; // best effort, skip failed points
        }
    }

    // In-memory index update
    EnsureIndex(collection_name);

    for (size_t i = 0; i < count; ++i) {
        runtimes_[collection_name].index->add(vectors[i].data(), point_id[i]);
    }
}

bool CollectionManager::UpsertPoints(
    const std::string& collection_name,
    const std::vector<int>& point_id,
    const std::vector<std::vector<float>>& vectors,
    const std::vector<nlohmann::json>& payload,
    int& operation_id
) {

    operation_id = 1999;  // placeholder for actual operation ID generation logic
    const size_t count = point_id.size();


    int coll_id=999; // placeholder for collection id for wal reference

    zoro::wal::WALWriter wal(root_path_+"/collections"+"/"+collection_name);

    for (size_t i = 0; i < count; ++i) {
        if (!wal.log_upsert_point(coll_id, point_id[i], vectors[i], payload[i])) {
            return false;
        }
    }

    std::thread([this, collection_name, point_id, vectors, payload, count, operation_id]() mutable {
        UpsertAsyncOperation(collection_name, point_id, vectors, payload, count, operation_id);
    }).detach();

    return true;
} 

}
