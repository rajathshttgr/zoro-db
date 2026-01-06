#include "../include/CollectionService.h"

namespace zoro::services {

CollectionService::CollectionService(zoro::core::CollectionManager* manager)
    : manager_(manager) {}

bool CollectionService::CreateCollection(const std::string& name, int dimension, const std::string& distance, std::string& err) {
    
    if (name.empty()) {
        err = "Collection name cannot be empty.";
        return false;
    }
    if (dimension <= 0) {
        err = "Dimension must be greater than zero.";
        return false;
    }

    // add distance enum validation

    if (!manager_->CreateCollection(name, dimension, distance)) {
        err = "Failed to create collection (already exists or storage error).";
        return false;
    }

    return true;
}

bool CollectionService::DeleteCollection(const std::string& name, std::string& err) {
    if (!manager_->DeleteCollection(name)) {
        err = "Failed to delete collection (does not exist or storage error).";
        return false;
    }
    return true;
}

std::vector<zoro::storage::CollectionInfo> CollectionService::ListCollections() const {
    return manager_->ListCollections();
}

std::optional<zoro::storage::CollectionInfo>
CollectionService::LoadCollection(const std::string& name, std::string& err) {
    auto result = manager_->LoadCollection(name);
    if (!result.has_value()) {
        err = "Collection not found.";
        return std::nullopt;
    }
    return result;
}



bool CollectionService::UpsertPointsService(const std::string& coll_name, const std::vector<int>& point_id, const std::vector<std::vector<float>> &vectors, const std::vector<nlohmann::json>& payload) {
    return manager_->UpsertPoints(coll_name, point_id, vectors, payload);
}

bool CollectionService::DeletePointsService(const std::string &coll_name, const std::vector<int> point_id) {
    return manager_->DeletePoints(coll_name, point_id);
}

int CollectionService::CountPointsService(const std::string &coll_name) {
    return manager_->CountPoints(coll_name);
}


std::optional<zoro::storage::PointInfo> CollectionService::RetrivePointById(const std::string& name, const int& point_id, std::string& err){
    auto result = manager_->RetrivePointById(name, point_id);
    if (!result.has_value()) {
        err = "Matching point not found.";
        return std::nullopt;
    }
    return result;
}

}