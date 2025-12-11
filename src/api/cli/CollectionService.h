#pragma once
#include <string>
#include <vector>
#include <optional>
#include "../../collection/include/CollectionManager.h"

namespace zoro::api {

class CollectionService {
public:
    explicit CollectionService(zoro::core::CollectionManager* manager);

    bool CreateCollection(const std::string& name, int dimension, std::string& err);
    bool DeleteCollection(const std::string& name, std::string& err);
    std::vector<std::string> ListCollections() const;
    std::optional<zoro::core::Collection> LoadCollection(const std::string& name, std::string& err);

private:
    zoro::core::CollectionManager* manager_;
};

}
