#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace zoro::storage{

using json = nlohmann::json;

struct CollectionInfo {
    int id;
    std::string coll_name;
    int dimension;
    std::string distance;
    std::string status;
    std::string created_at;
};

struct PointInfo{
    std::string status;
    int point_id;
    json payload;
};

struct SearchPointInfo{
    int point_id;
    int score;
    json payload;
};

struct VectorIndexEntry {
    uint64_t point_id;
    uint64_t offset;
    uint32_t length;
    uint8_t is_deleted;
};

}