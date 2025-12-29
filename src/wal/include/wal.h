#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "types.h"

namespace zoro::wal {

using json = nlohmann::json;

class WAL {
public:
    virtual ~WAL() = default;

    virtual bool log_create_collection(
        uint32_t coll_id,
        const std::string& name,
        uint32_t dimension,
        DistType distance
    ) = 0;

    virtual bool log_delete_collection(uint32_t coll_id) = 0;

    virtual bool log_upsert_point(
        uint32_t coll_id,
        uint64_t point_id,
        const std::vector<float>& vector,
        const json& payload
    )=0;

    virtual bool log_delete_point(uint32_t coll_id, uint64_t point_id)=0;
};

}
