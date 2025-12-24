#pragma once
#include <string>
#include <vector>
#include <optional>
#include "../../storage/include/StorageEngine.h"
#include "../../storage/include/struct.h"

namespace zoro::core{

class CollectionManager{
public:
    explicit CollectionManager(zoro::storage::StorageEngine* storage);
    bool CreateCollection(const std::string& name, int dimension,const std::string& distance);
    bool DeleteCollection(const std::string& name);

    std::vector<zoro::storage::CollectionInfo> ListCollections() const;
    std::optional<zoro::storage::CollectionInfo> LoadCollection(const std::string& name);

private:
    zoro::storage::StorageEngine* storage_;

};

}