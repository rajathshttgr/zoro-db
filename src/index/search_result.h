#pragma once
#include <cstdint>
#include <vector>

struct SearchResult {
    std::vector<uint64_t> point_ids;
    std::vector<float> distances;
};
