#pragma once
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "../../storage/include/StorageEngine.h"
#include "../../storage/include/struct.h"

namespace zoro::core{

using json = nlohmann::json;

class CollectionManager{
public:
    explicit CollectionManager(zoro::storage::StorageEngine* storage);
    bool CreateCollection(const std::string& name, int dimension,const std::string& distance);
    bool DeleteCollection(const std::string& name);

    std::vector<zoro::storage::CollectionInfo> ListCollections() const;
    std::optional<zoro::storage::CollectionInfo> LoadCollection(const std::string& name);

    bool UpsertPoints(const std::string& coll_name, const std::vector<int>& point_id, const std::vector<std::vector<float>>& vectors,const std::vector<nlohmann::json>& payload);
    bool DeletePoints(const std::string &coll_name, const std::vector<int> point_id);
    int CountPoints(const std::string &coll_name);

private:
    zoro::storage::StorageEngine* storage_;

};

}