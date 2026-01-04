#include "CollectionManager.h"
#include <filesystem>

namespace fs=std::filesystem;

namespace zoro::core {

CollectionManager::CollectionManager(const std::string& root_path, zoro::storage::StorageEngine* storage, zoro::wal::WAL& wal)
    : storage_(storage), wal_(wal), root_path_(root_path), catalog_(root_path) {
         fs::create_directories(root_path_);
    }

} 
