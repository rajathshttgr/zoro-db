#include "./CollectionService.h"
#include "./metadata_cache.h"
#include <thread>

namespace zoro::services {

void CollectionService::StartCacheRefresher() {
    std::thread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(30)); // refresh every 30 seconds, can be made configurable

            std::string err;
            std::vector<zoro::utils::CollectionMetadata> collections;

            if (!LoadCollections(collections, err)) {
                // log error, keep old cache
                continue;
            }

            auto new_cache = std::make_shared<MetadataCache>();

            for (const auto& coll : collections) {
                new_cache->put(coll.name, Metadata{
                    coll.size,
                    coll.distance,
                    coll.status
                });
            }

            // atomic swap 
            metadata_cache_.store(new_cache);
        }
    }).detach();
}

bool CollectionService::InitStartUp(std::string& err) {
    // load metadata and build cache
    std::vector<zoro::utils::CollectionMetadata> collections;
    
    if(!LoadCollections(collections, err)){
        return false;
    }

    auto new_cache = std::make_shared<MetadataCache>();

    for (const auto& coll : collections) {
        new_cache->put(coll.name, Metadata{coll.size, coll.distance, coll.status});
    }

    // atomically replace cache
    metadata_cache_.store(new_cache);
    // start background thread to refresh cache periodically
    StartCacheRefresher();

    return true;
}


void CollectionService::Shutdown(){
    // gracefull shutdown
}

}

// TODO: graceful shutdown handling for background thread