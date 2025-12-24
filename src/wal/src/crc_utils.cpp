#include "wal_writer.h"

namespace zoro::wal {

static uint32_t crc_table[256];
static bool table_initialized = false;

static void init_crc_table() {
    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t crc = i;
        for (int j = 0; j < 8; ++j) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
        crc_table[i] = crc;
    }
    table_initialized = true;
}

uint32_t WALWriter::crc_update(uint32_t crc, const uint8_t* data, size_t len) {
    if (!table_initialized) init_crc_table();

    for (size_t i = 0; i < len; ++i) {
        crc = crc_table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
    }
    return crc;
}

uint32_t WALWriter::calculate_crc(
    const LogEntryHeader& header,
    const std::vector<uint8_t>& payload
) {
    uint32_t crc = 0xFFFFFFFF;

    crc = crc_update(
        crc,
        reinterpret_cast<const uint8_t*>(&header),
        sizeof(LogEntryHeader) - sizeof(uint32_t) 
    );

    crc = crc_update(crc, payload.data(), payload.size());

    return crc ^ 0xFFFFFFFF;
}

}
