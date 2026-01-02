#pragma once
#include "struct.h"
#include "Catalog.h"
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "../../wal/include/wal.h"

namespace zoro::storage{

using json = nlohmann::json;

class StorageEngine {
public:
    explicit StorageEngine(const std::string& root_path,zoro::wal::WAL& wal);

    bool CreateCollection(const std::string& name, int dimension,std::string distance);
    bool DeleteCollection(const std::string& name);
    bool CollectionExists(const std::string& name) const;
    std::optional<CollectionInfo> GetCollectionInfo(const std::string& name) const;
    std::vector<CollectionInfo> ListCollections() const;

    bool UpsertPoints(const std::string& coll_name, int id, const std::vector<float> &vectors, const json& payload);
    bool DeletePoints(const std::string &coll_name, int point_id);
    int CountPoints(const std::string &coll_name);

private:
    std::string root_path_;
    std::string collection_root_;
    Catalog catalog_; 
    zoro::wal::WAL& wal_;
};

}