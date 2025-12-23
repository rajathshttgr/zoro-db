#pragma once

#include "types.h"
#include "struct.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs=std::filesystem;

namespace zoro::wal{

class WALWriter{
private:
    std::string root_path_;
    std::string wal_root_;
    uint32_t current_file_index;
    uint32_t entries_in_current_file;
    uint64_t current_lsn;
    std::ofstream current_file_stream;

public:
    explicit WALWriter(const std::string& root_path);
    ~WALWriter();

    bool append(OpType type, uint32_t coll_id, const std::vector<uint8_t>& payload);

private:
    void open_next_file();
    bool write_to_disk(const LogRecord& record);
    std::string format_index(uint32_t index);
    uint32_t calculate_crc(const LogEntryHeader& header, const std::vector<uint8_t>& payload);
    static uint32_t crc_update(uint32_t crc, const uint8_t* data, size_t len);

};

} 