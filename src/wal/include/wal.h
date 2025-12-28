#pragma once
#include <string>
#include "types.h"

namespace zoro::wal {

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
};

}
