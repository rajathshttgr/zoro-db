#pragma once
#include  <cstdint>

enum class OpType: uint8_t{
    CREATE_COLLECTION=1,
    DELETE_COLLECTION=2,
    UPSERT_POINT=3,
    DELETE_POINT=4,
};

const uint32_t MAX_ENTRIES_PER_FILE=100;
