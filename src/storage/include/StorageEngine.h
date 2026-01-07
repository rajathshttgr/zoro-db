#pragma once
#include "struct.h"
#include "Catalog.h"
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>

namespace zoro::storage{

using json = nlohmann::json;

class StorageEngine {
public:
    explicit StorageEngine(const std::string& root_path);

    bool CreateCollection(const std::string& collection_name, int dimension,std::string distance, int coll_id);
    bool DeleteCollection(const std::string& collection_name);
    bool CollectionExists(const std::string& collection_name) const;
    std::optional<CollectionInfo> GetCollectionInfo(const std::string& collection_name) const;
    std::vector<CollectionInfo> ListCollections() const;

    bool UpsertPoints(const std::string& collection_name, int id, const std::vector<float> &vectors, const json& payload);
    bool DeletePoints(const std::string& collection_name, int point_id);
    int CountPoints(const std::string& collection_name);
    std::optional<PointInfo> GetMetadataByPointId(const std::string& collection_name, int point_id, std::string& err);

private:
    std::string root_path_;
    std::string collection_root_;
    Catalog catalog_; 
};

}