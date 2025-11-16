#pragma once
#include <string>

struct StorageConfig{
    std::string storage_path;
    std::string snapshot_path;
};

struct Config{
    StorageConfig storage;
    std::string log_level;
    int http_port;

    static Config load(const std::string& filename);
};