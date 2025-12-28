#include "wal_writer.h"
#include "types.h"
#include "utils.h"

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


bool WALWriter::log_create_collection(
    uint32_t coll_id,
    const std::string& name,
    uint32_t dim,
    DistType distance
) {
    if (name.empty() || dim == 0) {
        return false;
    }

    std::vector<uint8_t> payload;
    payload.reserve(2 + name.size() + 4 + 1);

    append_u16(payload, static_cast<uint16_t>(name.size()));
    append_bytes(payload, name.data(), name.size());
    append_u32(payload, dim);
    append_u8(payload, static_cast<uint8_t>(distance));

    return append_central(
        OpType::CREATE_COLLECTION,
        coll_id,
        payload
    );
}


bool WALWriter::log_delete_collection(uint32_t coll_id){
    //logic
    std::vector<uint8_t> payload;

    return append_central(OpType::DELETE_COLLECTION, coll_id, payload);
}

// bool WALWriter::append_upsert_point(uint32_t coll_id, uint64_t point_id, const std::vector<float>& vector, const std::vector<uint8_t>& payload){
//     //logic
//     return append_central(UPSERT_POINT, coll_id, payload);
// }

// bool WALWriter::append_delete_point(uint32_t coll_id, uint64_t point_id){
//     //logic
//     return append_central(DELETE_POINT, coll_id, payload);
// }





bool WALWriter::append_central(
    OpType type,
    uint32_t coll_id,
    const std::vector<uint8_t>& binary_payload
) {
    if (entries_in_current_file >= MAX_ENTRIES_PER_FILE) {
        open_next_file();
    }

    LogRecord record;
    record.header.lsn = current_lsn++;
    record.header.type = type;
    record.header.collection_id = coll_id;
    record.header.payload_size =
        static_cast<uint32_t>(binary_payload.size());
    record.payload = binary_payload;

    record.header.crc32 =
        calculate_crc(record.header, record.payload);

    return write_to_disk(record);
}


}


