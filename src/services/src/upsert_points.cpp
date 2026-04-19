#include "./CollectionService.h"

namespace zoro::services {

bool CollectionService::UpsertPointsService(const std::string& name, const std::vector<zoro::utils::Points> points, int& operation_id, std::string& err){
    if (name.empty()) {
        err = "Collection name cannot be empty.";
        return false;
    }

    auto cache = metadata_cache_.load();

    Metadata result;
    if (cache && !cache->get(name, result)) {
        err = "Collection name `" + name + "` not found!";
        return false;
    }

    if(cache && result.status!="active"){
        err = "Collection is not in active state, collection current status "+result.status;
        return false;
    }
    
    std::vector<int> ids;
    std::vector<std::vector<float>> vectors;
    std::vector<json> payloads;

    for(zoro::utils::Points p : points){
        if(p.vectors.size() != result.size) {
            operation_id-=1;
            continue;
        }
        ids.push_back(p.id);
        vectors.push_back(p.vectors);
        payloads.push_back(p.payload);
    }

    if(!manager_->UpsertPoints(name, ids, vectors, payloads, operation_id)){
        err = "Something went wrong in Collection Manager [ER1620]";
    } 

    return true;
}

}