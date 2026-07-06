#pragma once
#include <string>

enum LogEntryType {
  UPSERT = 1,
  DELETE = 2,
};

class WriteAheadLog {
    public:
        WriteAheadLog(const std::string& collection_name);
        // ~WriteAheadLog();

        // bool log_entry(LogEntryType type, int point_id, const std::vector<float>& vector, const nlohmann::json& payload);
        // void log_replay(const std::string& log_file);
        // void log_cleanup(const std::string& log_file);
        // void log_rotate();

        bool test_log_file_exists(const std::string& collection_name);
};


/*
// Implementation Plan Summary

Log Write
Log Replay
Log Cleanup
Log Rotate

case 1: single file system
- append log at the end of the file
- return the lsn of the log entry
- update lsn in index tracker (acknowledgement)

case 2: multiple file system
- append log at the end of the file
- if the file size exceeds the threshold, rotate to a new file
- return the lsn of the log entry
- update lsn in index tracker (acknowledgement)

[op1] upsert a point
[op2] delete a point
[op3] delete a point

*/