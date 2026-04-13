#pragma once
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <atomic>
#include <nlohmann/json.hpp>
#include "../../collection/src/CollectionManager.h"
#include "../../utils/struct.h"
#include "./metadata_cache.h"

namespace zoro::services {

using json = nlohmann::json;

class CollectionService {
public:
    explicit CollectionService(zoro::core::CollectionManager* manager);

    // system startup
    bool InitStartUp(std::string& err);
    void StartCacheRefresher();
    void Shutdown();

    // collection management
    bool CreateCollection(const std::string& name, int& size,const std::string& distance, std::string& err);
    bool DeleteCollection(const std::string& name, std::string& err);
    bool CheckCollectionExists(const std::string& name, std::string& err);
    bool ListCollections(std::vector<zoro::utils::CollectionMetadata>& collections, std::string& err);
    bool GetCollectionInfo(const std::string& name, zoro::utils::CollectionInfo& collection, std::string& err);
    bool LoadCollections(std::vector<zoro::utils::CollectionMetadata>& collections, std::string& err);

    // point management
    bool UpsertPointsService(const std::string& coll_name, const std::vector<int>& point_id, const std::vector<std::vector<float>> &vectors, const std::vector<nlohmann::json>& payload);
    bool DeletePointsService(const std::string &coll_name, const std::vector<int> point_id);
    int CountPointsService(const std::string &coll_name);
    std::optional<zoro::utils::PointInfo> RetrivePointById(const std::string& name, const int& point_id, std::string& err);
    std::vector<zoro::utils::ScrollPointInfo> ScrollPointMetadata(const std::string& name, const int limit, std::string& err);
    std::vector<zoro::utils::SearchPointInfo> SearchPointByVector(const std::string& coll_name, const std::vector<float>& query_vector, int k, std::string& err);

    // deprecated
    //std::optional<zoro::utils::CollectionInfo> LoadCollection(const std::string& name, std::string& err);

private:
    zoro::core::CollectionManager* manager_;
    std::atomic<std::shared_ptr<MetadataCache>> metadata_cache_;
};

}
