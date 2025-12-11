#pragma once
#include <string>
#include <vector>

namespace zoro::storage {

class Catalog{
public:
    explicit Catalog(const std::string& root);

    bool AddCollection(const std::string& name);
    bool RemoveCollection(const std::string& name);
    std::vector<std::string> ListCollections() const;

private:
    std::string path_;
};

}