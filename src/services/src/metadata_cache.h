#pragma once
#include <string>
#include <unordered_map>

struct Metadata{
    int size{};      
    std::string distance{};   
    std::string status{};
};

class MetadataCache {
public:
    MetadataCache(){};
        
    const std::unordered_map<std::string, Metadata>& data() const {
        return cacheMap;
    }

    bool get(const std::string &key, Metadata& result){
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) return false;

        result = it->second;
        return true;
    };

    bool put(const std::string &key, const Metadata &metadata){
        cacheMap[key] = metadata;
        return true;
    };

    void remove(const std::string &key){
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) return;
        cacheMap.erase(it);
    };

private:
    std::unordered_map<std::string, Metadata> cacheMap;
};