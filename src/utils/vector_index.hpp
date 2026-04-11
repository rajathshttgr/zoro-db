#pragma once
#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>

namespace zoro::utils {

using json = nlohmann::json;

struct PointInfo{
    std::string status;
    int point_id;
    json payload;
};

struct ScrollPointInfo{
    int point_id;
    json payload;
};

struct SearchPointInfo{
    int point_id;
    float score;
    json payload;
};

struct VectorIndexEntry {
    uint64_t point_id;
    uint64_t offset;
    uint32_t length;
    uint8_t is_deleted;
};

}