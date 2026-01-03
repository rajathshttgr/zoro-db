#pragma once

#include <cstdint>
#include <vector>
#include "search_result.h"

class VectorIndex {

public:
    virtual ~VectorIndex() = default;

    virtual void build(const std::vector<float>& vectors, const std::vector<uint64_t>& point_ids) = 0;

    virtual void add(const float* vectors, const uint64_t point_id) = 0;
    virtual void remove(const uint64_t point_id) = 0;

    virtual SearchResult search(const float* query, uint32_t k) const = 0;

    virtual size_t size() const = 0;

};