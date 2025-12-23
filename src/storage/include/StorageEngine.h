#pragma once
#include <string>
#include <vector>
#include <optional>
#include "../../wal/include/wal_writer.h"

namespace zoro::storage{

struct CollectionInfo {
    std::string name;
    std::string path;
};

class StorageEngine {
public:
    explicit StorageEngine(const std::string& root_path,zoro::wal::WALWriter* wal);
    // explicit StorageEngine(zoro::wal::WALWriter* wal);

    bool CreateCollection(const std::string& name);
    bool DeleteCollection(const std::string& name);
    bool CollectionExists(const std::string& name) const;
    std::optional<CollectionInfo> GetCollectionInfo(const std::string& name) const;
    std::vector<CollectionInfo> ListCollections() const;

private:
    std::string root_path_;
    std::string collection_root_;
    zoro::wal::WALWriter* wal_;
};

}