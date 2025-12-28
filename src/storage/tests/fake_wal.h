#include "../../wal/include/wal.h"

class FakeWAL : public zoro::wal::WAL {
public:
    int create_calls = 0;
    int delete_calls = 0;

    bool log_create_collection(
        uint32_t,
        const std::string&,
        uint32_t,
        DistType
    ) override {
        create_calls++;
        return true;
    }

    bool log_delete_collection(uint32_t) override {
        delete_calls++;
        return true;
    }
};
