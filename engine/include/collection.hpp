#pragma once

#include "vector.hpp"
#include <string>
#include <unordered_map>
#include <mutex>

namespace zoro{

class Collection{
public:
    Collection(const std::string& name, int dimension);
    ~Collection();
    bool insert(const Vector& v);
    bool get(const std::string& id, Vector& out) const;
    size_t size() const;
    int dimension() const;
    const std::string& name() const;

private:
    std::string name_;
    int dim_;
    mutable std::mutex mu_;
    std::unordered_map<std::string, std::vector<float>> storage_;
};
}