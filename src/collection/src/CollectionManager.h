#pragma once
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include "collection_runtime.h"
#include "../../storage/include/StorageEngine.h"
#include "../../storage/include/struct.h"
#include "../../utils/struct.h"
#include "../../storage/include/Catalog.h"
#include "../../wal/include/wal.h"

namespace zoro::core{

using json = nlohmann::json;

class CollectionManager{
public:
    explicit CollectionManager(const std::string& root_path, zoro::storage::StorageEngine* storage, zoro::wal::WAL& wal);
    bool EnsureIndex(const std::string& name);

    bool CreateCollection(const std::string& name, int dimension,const std::string& distance, std::string& err);
    bool DeleteCollection(const std::string& name, std::string& err);
    bool LoadCollections(std::vector<zoro::utils::CollectionMetadata>& collections, std::string& err);
    bool CollectionExists(const std::string& name, std::string& err); 
    bool GetCollection(const std::string& name, zoro::utils::CollectionInfo& collection, std::string& err); 
    
    bool UpsertPoints(const std::string& coll_name, const std::vector<int>& point_id, const std::vector<std::vector<float>>& vectors,const std::vector<nlohmann::json>& payload);
    bool DeletePoints(const std::string &coll_name, const std::vector<int> point_id);
    int CountPoints(const std::string &coll_name);

    std::optional<zoro::utils::PointInfo> RetrivePointById(const std::string& coll_name, const int& point_id, std::string& err);
    std::vector<zoro::utils::ScrollPointInfo> ScrollPointMetadata(const std::string& coll_name, const int limit, std::string& err);

    std::vector<zoro::utils::SearchPointInfo> SearchPointByVector(const std::string& coll_name, const std::vector<float>& query_vector, int k);

    // DEPRECATED
    // deprecated, now it relies on LoadCollections and data is stored in cache.
    std::vector<zoro::utils::CollectionInfo> ListCollections() const;
    // deprecated, use GetCollection instead
    std::optional<zoro::utils::CollectionInfo> LoadCollection(const std::string& name);

private:
    std::string root_path_;
    zoro::storage::StorageEngine* storage_;
    zoro::storage::Catalog catalog_; 
    zoro::wal::WAL& wal_;

    std::unordered_map<std::string, CollectionRuntime> runtimes_;
};

}