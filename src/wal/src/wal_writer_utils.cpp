#include "wal_writer.h" 

namespace zoro::wal{

void WALWriter::open_next_file() {
    if (current_file_stream.is_open())
        current_file_stream.close();

    current_file_index++;
    entries_in_current_file = 0;

    std::string filename = wal_root_ + "/wal_" + format_index(current_file_index) + ".log";

    current_file_stream.open(filename, std::ios::binary | std::ios::out);
    if (!current_file_stream.is_open()) {
        throw std::runtime_error("Failed to open WAL file: " + filename);
    }

    WALFileHeader file_header = {0x57414C44, 1, 0, current_lsn};
    current_file_stream.write(reinterpret_cast<const char*>(&file_header), sizeof(WALFileHeader));
    current_file_stream.flush();
}


std::string WALWriter::format_index(uint32_t index){
    std::ostringstream oss;
    oss<<std::setw(4)<<std::setfill('0')<<index;
    return oss.str();
}

bool WALWriter::write_to_disk(const LogRecord& record){
    current_file_stream.write(reinterpret_cast<const char*>(&record.header),sizeof(LogEntryHeader));

    current_file_stream.write(reinterpret_cast<const char*>(record.payload.data()),record.payload.size());

    current_file_stream.flush();

    entries_in_current_file++;
    return true;
}

}