#pragma once
#include <string>
#include <vector>
#include <optional>
#include "Collection.h"
#include "../../storage/include/StorageEngine.h"

namespace zoro::core{

class CollectionManager{
public:
    explicit CollectionManager(zoro::storage::StorageEngine* storage);
    bool CreateCollection(const std::string& name, int dimension,const std::string& distance);
    bool DeleteCollection(const std::string& name);

    std::vector<std::string> ListCollections() const;
    std::optional<Collection> LoadCollection(const std::string& name);

private:
    zoro::storage::StorageEngine* storage_;

};

}