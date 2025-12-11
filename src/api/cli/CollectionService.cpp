#include "CollectionService.h"

namespace zoro::api {

CollectionService::CollectionService(zoro::core::CollectionManager* manager)
    : manager_(manager) {}

bool CollectionService::CreateCollection(const std::string& name, int dimension, std::string& err) {
    if (name.empty()) {
        err = "Collection name cannot be empty.";
        return false;
    }
    if (dimension <= 0) {
        err = "Dimension must be greater than zero.";
        return false;
    }

    if (!manager_->CreateCollection(name, dimension)) {
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

std::vector<std::string> CollectionService::ListCollections() const {
    return manager_->ListCollections();
}

std::optional<zoro::core::Collection>
CollectionService::LoadCollection(const std::string& name, std::string& err) {
    auto result = manager_->LoadCollection(name);
    if (!result.has_value()) {
        err = "Collection not found.";
        return std::nullopt;
    }
    return result;
}

}
