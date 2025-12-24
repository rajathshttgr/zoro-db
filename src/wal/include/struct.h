#pragma once

#include "types.h"
#include  <cstdint>
#include <vector>
#include <memory>

struct WALFileHeader{
    uint32_t magic_number;
    uint16_t version;
    uint16_t reserved;
    uint64_t start_lsn;
    uint32_t crc32; 
};

#pragma pack(push,1) //ensures no padding between members

struct LogEntryHeader{
    uint64_t lsn;
    OpType type;
    uint32_t collection_id;
    uint32_t payload_size;
    uint32_t crc32;
};

#pragma pack(pop)


struct LogRecord {
    LogEntryHeader header;
    std::vector<uint8_t> payload;

    size_t total_size() const{
        return sizeof(LogEntryHeader)+payload.size();
    }
};