#pragma once
#include <cstdint>
#include <vector>

namespace zoro::wal {

void append_u8(std::vector<uint8_t>& buf, uint8_t v);
void append_u16(std::vector<uint8_t>& buf, uint16_t v);
void append_u32(std::vector<uint8_t>& buf, uint32_t v);
void append_u64(std::vector<uint8_t>& buf, uint64_t v);
void append_bytes(std::vector<uint8_t>& buf, const void* data, size_t len);

}
