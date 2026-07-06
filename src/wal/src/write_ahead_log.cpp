#include "write_ahead_log.h"
#include "file_utils.h"
#include "../../config.h"

#include <string>

WriteAheadLog::WriteAheadLog(const std::string& collection_name) {
    std::string storage_path = zoro::config::getStoragePath() + "/" + collection_name + "/wal";
    if(!create_directory(storage_path)){
        throw std::runtime_error("Failed to create log directory: " + storage_path);
    }
}

bool WriteAheadLog::test_log_file_exists(const std::string& collection_name) {
    std::string storage_path = zoro::config::getStoragePath() + "/" + collection_name + "/wal";
    return file_exists(storage_path);
}