#pragma once
#include <string>
#include <vector>
#include <optional>
#include "../../collection/include/CollectionManager.h"
#include "../../storage/include/struct.h"

namespace zoro::services {

class CollectionService {
public:
    explicit CollectionService(zoro::core::CollectionManager* manager);

    bool CreateCollection(const std::string& name, int dimension,const std::string& distance, std::string& err);
    bool DeleteCollection(const std::string& name, std::string& err);
    std::vector<zoro::storage::CollectionInfo> ListCollections() const;
    std::optional<zoro::storage::CollectionInfo> LoadCollection(const std::string& name, std::string& err);

private:
    zoro::core::CollectionManager* manager_;
};

}
