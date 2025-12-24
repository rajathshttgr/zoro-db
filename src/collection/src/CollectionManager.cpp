#include "CollectionManager.h"
// #include "../../storage/include/CollectionMeta.h"

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
}