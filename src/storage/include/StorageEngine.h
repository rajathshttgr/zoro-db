#pragma once
#include "struct.h"
#include "Catalog.h"
#include <string>
#include <vector>
#include <optional>
#include "../../wal/include/wal_writer.h"

namespace zoro::storage{

class StorageEngine {
public:
    explicit StorageEngine(const std::string& root_path,zoro::wal::WALWriter* wal);

    bool CreateCollection(const std::string& name, int dimension,std::string distance);
    bool DeleteCollection(const std::string& name);
    bool CollectionExists(const std::string& name) const;
    std::optional<CollectionInfo> GetCollectionInfo(const std::string& name) const;
    std::vector<CollectionInfo> ListCollections() const;

private:
    std::string root_path_;
    std::string collection_root_;
    Catalog catalog_; 
    zoro::wal::WALWriter* wal_;
};

}