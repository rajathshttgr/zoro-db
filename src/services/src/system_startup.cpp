#include "./CollectionService.h"
#include "./metadata_cache.h"

namespace zoro::services {

bool CollectionService::InitStartUp() {
    // load metadata and build cache
    std::vector<zoro::utils::CollectionMetadata> collections;
    std::string err;
    if(!LoadCollections(collections, err)){
        return false;
    }

    for(auto coll : collections){
        metadata_cache_.put(coll.name, Metadata{coll.size, coll.distance, coll.status});
    }
    return true;
}
}

// TODO: Periodic Rebuild, no downtime update