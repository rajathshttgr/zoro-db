#pragma once

#include "collection.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace zoro{

class Engine{
public:
    Engine();
    ~Engine();

    bool create_collection(const std::string& name, int dimension);
    // bool has_collection(const std::string& name) const;
    // std::shared_ptr<Collection> get_collection(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Collection>> collections;
};
}