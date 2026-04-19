#include "CollectionManager.h"
#include "../../storage/include/Distance_utils.h"
#include "../../wal/include/wal_writer.h"

namespace zoro::core {

bool CollectionManager::DeletePoints(
    const std::string& collection_name,
    const std::vector<int> point_id
) {

    if (!storage_->CollectionExists(collection_name)) {
        return false;
    }

    int coll_id=catalog_.GetCollectionId(collection_name);

    zoro::wal::WALWriter wal(root_path_+"/collections"+"/"+collection_name);
    // Append to WAL
    for (int id : point_id) {
        if (!wal.log_delete_point(coll_id, id)) {
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



std::vector<zoro::utils::SearchPointInfo>
CollectionManager::SearchPointByVector(
    const std::string& coll_name,
    const std::vector<float>& query_vector,
    int k
) {
    std::vector<zoro::utils::SearchPointInfo> output;

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

        zoro::utils::SearchPointInfo info;
        info.point_id = point_id;

        // score strategy (simple version)
        info.score = result.distances[i];

        info.payload = meta->payload;

        output.push_back(std::move(info));
    }

    return output;
}


std::optional<zoro::utils::PointInfo>
CollectionManager::RetrivePointById(const std::string& name, const int& point_id, std::string& err){
    if (!storage_->CollectionExists(name)) {
        err = "Matching point not found.";
        return std::nullopt;
    }
    return storage_->GetMetadataByPointId(name, point_id, err);
}


std::vector<zoro::utils::ScrollPointInfo> 
CollectionManager::ScrollPointMetadata(const std::string& coll_name, const int limit, std::string& err){
    if (!storage_->CollectionExists(coll_name)) {
        err = "collection doesn't exist in the system!";
        return {};
    }
    return storage_->ListPointMetadata(coll_name, limit, err);
}

} // namespace zoro::core


