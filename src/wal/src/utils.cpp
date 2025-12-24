#include "utils.h"
#include <cstring>

namespace zoro::wal {

void append_u8(std::vector<uint8_t>& buf, uint8_t v) {
    buf.push_back(v);
}

void append_u16(std::vector<uint8_t>& buf, uint16_t v) {
    uint8_t* p = reinterpret_cast<uint8_t*>(&v);
    buf.insert(buf.end(), p, p + sizeof(v));
}

void append_u32(std::vector<uint8_t>& buf, uint32_t v) {
    uint8_t* p = reinterpret_cast<uint8_t*>(&v);
    buf.insert(buf.end(), p, p + sizeof(v));
}

void append_u64(std::vector<uint8_t>& buf, uint64_t v) {
    uint8_t* p = reinterpret_cast<uint8_t*>(&v);
    buf.insert(buf.end(), p, p + sizeof(v));
}

void append_bytes(std::vector<uint8_t>& buf, const void* data, size_t len) {
    const uint8_t* p = reinterpret_cast<const uint8_t*>(data);
    buf.insert(buf.end(), p, p + len);
}

}
