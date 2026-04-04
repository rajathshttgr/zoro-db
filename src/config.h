#pragma once
#include <string>
#include <cstdlib>

namespace zoro {
namespace config {

std::string SYSTEM_VERSION="v0.2.0";
// system version tracks the major changes in updation and retrival of data.

std::string STORAGE_VERSION="v1";
// storage version logs will be updated in docs.
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

    return "/storage"; 
}
// persistent storage path, default uses '/storage', build script uses default path '/.zoro-data'

} 
} 
