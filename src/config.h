#pragma once
#include <string>
#include <cstdlib>

namespace zoro {
namespace config {

inline std::string getVersion(){
    std::string VERSION="v0.2.0";
    return VERSION;
}

inline std::string getDataPath() {
    const char* env_path = std::getenv("ZORO_DATA_PATH");
    if (env_path && std::string(env_path).size() > 0)
        return std::string(env_path);

    return "/storage"; 
}

} 
} 
