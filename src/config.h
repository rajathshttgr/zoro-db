#pragma once
#include <string>
#include <cstdlib>

namespace zoro {
namespace config {

inline std::string SYSTEM_VERSION = "v0.2.0";
// system version tracks the major changes in updation and retrival of data.

inline std::string STORAGE_VERSION = "v1";
// storage version tracks how data is stored on disk.

inline std::string getVersion(){
    return SYSTEM_VERSION;
}

inline std::string getStorageVersion(){
    return STORAGE_VERSION;
}

inline std::string getDataPath() {
    const char* env_path = std::getenv("ZORO_DATA_PATH");
    if (env_path && std::string(env_path).size() > 0)
        return std::string(env_path);

    // persistent storage path, default uses '/.storage'
    return "/.storage"; 
}

} 
}