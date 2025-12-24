#pragma once
#include <string>

namespace zoro::storage{

struct CollectionInfo {
    int id;
    std::string coll_name;
    int dimension;
    std::string distance;
    std::string status;
    std::string created_at;
};

}