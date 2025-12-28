#pragma once
#include "wal.h"

namespace zoro::wal {

class NullWAL final : public WAL {
public:
    bool log_create_collection(
        uint32_t,
        const std::string&,
        uint32_t,
        DistType
    ) override {
        return true;
    }

    bool log_delete_collection(uint32_t) override {
        return true;
    }
};

}
