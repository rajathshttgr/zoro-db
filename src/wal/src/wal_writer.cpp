#include "wal_writer.h"
#include "types.h"

namespace zoro::wal{

WALWriter::WALWriter(const std::string& root_path)
    : root_path_(root_path),
      wal_root_(root_path + "/wal"),
      current_file_index(0),
      entries_in_current_file(0),
      current_lsn(1) {
  std::filesystem::create_directories(root_path_);
  std::filesystem::create_directories(wal_root_);

  open_next_file();
}

WALWriter::~WALWriter(){
    if(current_file_stream.is_open()){
        current_file_stream.close();
    }
}

bool WALWriter::append(OpType type, uint32_t coll_id, const std::vector<uint8_t>& payload){
    if(entries_in_current_file>=MAX_ENTRIES_PER_FILE){
        open_next_file();
    }
    LogRecord record;
    record.header.lsn=current_lsn++;
    record.header.type=type;
    record.header.collection_id=coll_id;
    record.header.payload_size=static_cast<uint32_t>(payload.size());
    record.payload=payload;
    // calculate crc checksum and update
    record.header.crc32 = calculate_crc(record.header, record.payload);

    return write_to_disk(record);
}

}