#include "CollectionManager.h"
#include <filesystem>
#include "../../index/faiss/faiss_config.h"
#include "../../index/distance_metric_utils.h"
#include "../../index/index_factory.h"

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
    if (runtimes_.count(name)) {
        return true;
    }

    auto info = storage_->GetCollectionInfo(name);
    if (!info) {
        return false;
    }

    FaissConfig config;
    config.dimension = info->dimension;
    config.metric = DistanceMetricFromString(info->distance);

    CollectionRuntime runtime;
    runtime.index = IndexFactory::create_faiss_index(config);
    runtime.dimension = info->dimension;

    runtimes_[name] = std::move(runtime);
    return true;
}

}
