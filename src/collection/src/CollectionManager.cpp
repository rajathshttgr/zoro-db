#include "CollectionManager.h"

namespace zoro::core{

CollectionManager::CollectionManager(zoro::storage::StorageEngine* storage):storage_(storage){};

bool CollectionManager::CreateCollection(const std::string& name, int dimension,const std::string& distance){
    if(storage_->CollectionExists(name)) return false;

    if(!storage_->CreateCollection(name,dimension,distance)) return false;

    return true;
}

bool CollectionManager::DeleteCollection(const std::string& name){
    return storage_->DeleteCollection(name);
}


std::vector<zoro::storage::CollectionInfo> CollectionManager::ListCollections() const{
    auto collection_list=storage_->ListCollections();
    return collection_list;
}

std::optional<zoro::storage::CollectionInfo> CollectionManager::LoadCollection(const std::string& name){
    if(!storage_->CollectionExists(name)){
        return std::nullopt;
    }

    auto info=storage_->GetCollectionInfo(name);

    return info;
};


bool CollectionManager::UpsertPoints(
    const std::string& coll_name,
    const std::vector<int>& point_id,
    const std::vector<std::vector<float>>& vectors,
    const std::vector<nlohmann::json>& payload
) {
    const size_t count = point_id.size();

    // input validation
    if (count == 0 ||
        vectors.size() != count ||
        payload.size() != count) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {

        const bool success = storage_->UpsertPoints(
            coll_name,
            point_id[i],
            vectors[i],
            payload[i]
        );

        if (!success) {
            return false;
        }
    }

    return true;
}


bool CollectionManager::DeletePoints(const std::string &coll_name, const std::vector<int> point_id){

    for(int i: point_id){
        const bool success = storage_->DeletePoints(coll_name,i);
        if (!success) {
            return false;
        }
    }
    return true;
}


int CollectionManager::CountPoints(const std::string& coll_name){
    if(!storage_->CollectionExists(coll_name)) return -1;
    return storage_->CountPoints(coll_name);
}

}