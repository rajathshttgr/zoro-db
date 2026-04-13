#include "./CollectionService.h"

namespace zoro::services {

bool CollectionService::UpsertPointsService(const std::string& coll_name, const std::vector<int>& point_id, const std::vector<std::vector<float>> &vectors, const std::vector<nlohmann::json>& payload) {
    auto cache = metadata_cache_.load();
    Metadata result;
    if (cache && !cache->get(coll_name, result)) {
        return false;
    }
    if(cache && result.status!="active"){
        return false;
    }
    if(cache && result.size != vectors[0].size()) {
        return false;
    }
    return manager_->UpsertPoints(coll_name, point_id, vectors, payload);
}

bool CollectionService::DeletePointsService(const std::string &coll_name, const std::vector<int> point_id) {
    return manager_->DeletePoints(coll_name, point_id);
}

int CollectionService::CountPointsService(const std::string &coll_name) {
    return manager_->CountPoints(coll_name);
}

std::optional<zoro::utils::PointInfo> CollectionService::RetrivePointById(const std::string& name, const int& point_id, std::string& err){
    auto result = manager_->RetrivePointById(name, point_id, err);
    if (!result.has_value()) {
        err = "Matching point not found in collection.";
        return std::nullopt;
    }
    return result;
}

std::vector<zoro::utils::ScrollPointInfo> CollectionService::ScrollPointMetadata(const std::string& name, const int limit, std::string& err){
    if (limit <= 0) {
        err = "limit should be atleast 1";
        return {};
    }
    auto result= manager_->ScrollPointMetadata(name, limit, err);
    return result;
}

}