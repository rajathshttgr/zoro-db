#include "../include/CollectionService.h"
#include <unordered_map>


namespace zoro::services {

    bool CollectionService::CreateCollection(const std::string& name, int size, const std::string& distance, std::string& err){
        if (name.empty()) {
            err = "Collection name cannot be empty.";
            return false;
        }

        if (!manager_->CreateCollection(name, size, distance, err)) {
            if(err.empty()) {
                err = "Failed to create collection, storage error.";
            }
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

