#pragma once
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "../../collection/include/CollectionManager.h"
#include "../../storage/include/struct.h"

namespace zoro::services {

using json = nlohmann::json;

class CollectionService {
public:
    explicit CollectionService(zoro::core::CollectionManager* manager);

    bool CreateCollection(const std::string& name, int dimension,const std::string& distance, std::string& err);
    bool DeleteCollection(const std::string& name, std::string& err);
    std::vector<zoro::storage::CollectionInfo> ListCollections() const;
    std::optional<zoro::storage::CollectionInfo> LoadCollection(const std::string& name, std::string& err);

    bool UpsertPointsService(const std::string& coll_name, const std::vector<int>& point_id, const std::vector<std::vector<float>> &vectors, const std::vector<nlohmann::json>& payload);
    bool DeletePointsService(const std::string &coll_name, const std::vector<int> point_id);
    int CountPointsService(const std::string &coll_name);

    std::optional<zoro::storage::PointInfo> RetrivePointById(const std::string& name, const int& point_id, std::string& err);

private:
    zoro::core::CollectionManager* manager_;
};

}
