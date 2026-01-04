#pragma once
#include "struct.h"
#include <string>
#include <vector>
#include <optional>

namespace zoro::storage {

class Catalog{
public:
    explicit Catalog(const std::string& root);

    bool AddCollection(const std::string& name, int& coll_id, int& dimension, const std::string& distance);
    bool CollectionExists(const std::string& name) const;
    int GetCollectionId(const std::string& name);
    std::optional<CollectionInfo>  GetCollectionInfo(const std::string& name) const;
    bool RemoveCollection(const std::string& name);
    std::vector<CollectionInfo> ListCollections() const;

private:
    std::string path_;
};

}