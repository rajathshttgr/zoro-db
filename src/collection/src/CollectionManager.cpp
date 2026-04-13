#include "CollectionManager.h"
#include <filesystem>
#include "../../index/faiss/faiss_config.h"
#include "../../index/distance_metric_utils.h"
#include "../../index/index_factory.h"
#include "../../utils/struct.h"

namespace fs=std::filesystem;

namespace zoro::core {

CollectionManager::CollectionManager(
    const std::string& root_path,
    zoro::storage::StorageEngine* storage,
    zoro::wal::WAL& wal
)
    : root_path_(root_path),
      storage_(storage),
      catalog_(root_path),
      wal_(wal) {
    fs::create_directories(root_path_);
}

bool CollectionManager::EnsureIndex(const std::string& name) {
    auto& runtime = runtimes_[name];

    if (!runtime.index) {
        // deprecated function replace if required
        //bool StorageEngine::GetCollection(zoro::utils::CollectionInfo& collection, const std::string& collection_name, std::string& err){
        // auto info = storage_->GetCollectionInfo(name);

        zoro::utils::CollectionInfo collection;
        std::string err;
        if (!storage_->GetCollection(collection, name, err)) {
            return false;
        }

        FaissConfig config;
        config.dimension = collection.size; //info->dimension;
        config.metric = DistanceMetricFromString(collection.distance);

        runtime.index = IndexFactory::create_faiss_index(config);
        runtime.built = false;
    }

    if (!runtime.built) {
        std::vector<float> vectors;
        std::vector<uint64_t> ids;

        storage_->LoadAllVectors(name, vectors, ids); 

        if (!vectors.empty()) {
            runtime.index->build(vectors, ids);
        }

        runtime.built = true;
    }
    
    return true;
}

}
