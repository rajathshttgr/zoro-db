#include "CollectionManager.h"
#include "../../storage/include/CollectionMeta.h"

namespace zoro::core{

CollectionManager::CollectionManager(zoro::storage::StorageEngine* storage):storage_(storage){};

bool CollectionManager::CreateCollection(const std::string& name, int dimension,const std::string& distance){
    if(storage_->CollectionExists(name)) return false;

    if(!storage_->CreateCollection(name,dimension,distance)) return false;

    auto info=storage_->GetCollectionInfo(name);
    if(!info) return false;

    // mostly this operation is optional, it overwrites default initialization
    zoro::storage::CollectionMeta meta(info->path);
    meta.SetDimensions(dimension);

    return true;
}

bool CollectionManager::DeleteCollection(const std::string& name){
    return storage_->DeleteCollection(name);
}

std::vector<std::string> CollectionManager::ListCollections() const{
    auto list=storage_->ListCollections();
    std::vector<std::string> names;
    for(auto& item: list){
        names.push_back(item.name);
    }
    return names;
}

std::optional<Collection> CollectionManager::LoadCollection(const std::string& name){
    if(!storage_->CollectionExists(name)){
        return std::nullopt;
    }

    auto info=storage_->GetCollectionInfo(name);
    zoro::storage::CollectionMeta meta(info->path);

    int dim=meta.GetDimensions();
    return Collection(name,dim);

};
}