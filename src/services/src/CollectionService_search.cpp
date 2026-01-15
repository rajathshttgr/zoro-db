#include "../include/CollectionService.h"

namespace zoro::services {

std::vector<zoro::storage::SearchPointInfo> CollectionService::SearchPointByVector(const std::string& coll_name, const std::vector<float>& query_vector, int k, std::string& err){
    if (coll_name.empty()) {
        err = "Collection name cannot be empty.";
        return {};
    }
    if (k <= 0) {
        err = "k can't be less than or equal to 0";
        return {};
    }
    auto coll = manager_->LoadCollection(coll_name);
    if (!coll.has_value()) {
        err = "Collection not found.";
        return {};
    }
    if (query_vector.empty()) {
        err = "Query vector cannot be empty.";
        return {};
    }
    if (static_cast<int>(query_vector.size()) != coll->dimension) {
        err = "Query vector dimension mismatch.";
        return {};
    }
    for (float x : query_vector) {
        if (!std::isfinite(x)) {
            err = "Query vector contains non-finite values.";
            return {};
        }
    }

    return manager_->SearchPointByVector(coll_name, query_vector, k);
}

}