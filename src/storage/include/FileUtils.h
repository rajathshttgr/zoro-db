#pragma once
#include "../include/Utils.h"
#include <string>
#include <cstdint>

namespace zoro::storage{

class FileUtils {
public:
    static bool Exists(const std::string& path);
    static bool CreateFileIfNotExists(const std::string& path);
    static bool WriteText(const std::string& path, const std::string& content);
    static bool WriteBinary(const std::string& path, const char* data, size_t size);
    static std::string ReadText(const std::string& path);

    static uint64_t appendBinaryData(const std::string& path,const char* data, uint64_t size_bytes);
    static IndexUpdateResult updateIndexFile(const std::string& path, uint32_t id, uint64_t offset, uint32_t length, uint8_t flag_delete = 0);

    static bool findPayloadIndex(const std::string& idx_path, uint32_t target_id, uint64_t& out_offset, uint32_t& out_length);
    static std::string readBinaryData(const std::string& path, uint64_t offset, uint32_t length);
};
}