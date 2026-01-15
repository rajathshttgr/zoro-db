#include "../include/CollectionService.h"

namespace zoro::services {

    bool CollectionService::CreateCollection(const std::string& name, int dimension,const std::string& distance, std::string& err){
        if (name.empty()) {
            err = "Collection name cannot be empty.";
            return false;
        }
        if (dimension <= 0) {
            err = "Dimension must be greater than zero.";
            return false;
        }

        // distance enum validation
        if (distance != "l2" && distance != "cosine" && distance != "dot") {
            err = "Invalid distance metric. Must be one of: l2, cosine, dot.";
            return false;
        }

        if (!manager_->CreateCollection(name, dimension, distance)) {
            err = "Failed to create collection, name already exists.";
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


}

