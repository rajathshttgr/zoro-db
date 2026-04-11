#pragma once
#include <string>
#include "vector_index.hpp"

namespace zoro::utils{

// collection metadata
struct CollectionMetadata {
    std::string name;
    int size;
    std::string distance;
    std::string status;
};

// collection info with all metadata details
struct CollectionInfo {
    std::string name;
    int size;
    std::string distance;
    std::string status;

    // detailed metadata
    int points_count;
    int segments_count;
    std::string collection_id;
    std::string created_at;
    std::string updated_at;

    // index config attached at collection level
    std::string index;
    bool gpu_support;
    bool parallel_boost;

    // deprecated - to remove
    int id;
    int dimension;
    std::string coll_name;
};

}