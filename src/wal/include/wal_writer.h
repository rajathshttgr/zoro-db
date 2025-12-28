#pragma once

#include "types.h"
#include "struct.h"
#include "wal.h" 
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs=std::filesystem;

namespace zoro::wal{

class WALWriter: public WAL{
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

    bool log_create_collection(uint32_t coll_id, const std::string& name, uint32_t dim, DistType distance) override;

    bool log_delete_collection(uint32_t coll_id) override;
    
    // bool append_upsert_point(uint32_t coll_id, uint64_t point_id, const std::vector<float>& vector, const std::vector<uint8_t>& payload);
    // bool append_delete_point(uint32_t coll_id, uint64_t point_id);

private:
    bool append_central(OpType type, uint32_t coll_id, const std::vector<uint8_t>& binary_payload);
    void open_next_file();
    bool write_to_disk(const LogRecord& record);
    std::string format_index(uint32_t index);
    uint32_t calculate_crc(const LogEntryHeader& header, const std::vector<uint8_t>& payload);
    static uint32_t crc_update(uint32_t crc, const uint8_t* data, size_t len);

};

} 