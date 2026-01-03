#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>

class FaissIdMap{
public:
    void add(uint64_t point_id);
    uint64_t get_point_id(uint64_t faiss_internal_id) const;

    void mark_deleted(uint64_t point_id);
    bool is_deleted(uint64_t point_id) const;

    size_t size() const;
    void clear();

private:
    std::vector<uint64_t> internal_to_point_;
    std::unordered_map<uint64_t, uint64_t> point_to_internal_;
};