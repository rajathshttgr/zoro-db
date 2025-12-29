#pragma once
#include "wal.h"

namespace zoro::wal {

class NullWAL final : public WAL {
public:
    bool log_create_collection( uint32_t, const std::string&, uint32_t, DistType) override {
        return true;
    }

    bool log_delete_collection(uint32_t) override {
        return true;
    }

    bool log_upsert_point(uint32_t coll_id, uint64_t point_id, const std::vector<float>& vector,const json& payload) override{
        return true;
    }
    
    bool log_delete_point(uint32_t coll_id, uint64_t point_id) override{
        return true;
    }
};

}
