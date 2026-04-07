#include "./CollectionService.h"
#include "./metadata_cache.h"


namespace zoro::services {

    bool CollectionService::CreateCollection(const std::string& name, int& size, const std::string& distance, std::string& err){
        // basic input data validations are done at api layer, below validation can be removed or improved bbased on dev requirements
        if (name.empty()) {
            err = "Collection name cannot be empty.";
            return false;
        }

        // check cache 
        Metadata result;
        if (metadata_cache_.get(name, result)) {
            if(result.status=="active"){
                err = "Collection name `" + name + "` already exists!";
                return false;
            }
        }
        // Note: during concurrent requests, even if collection is deleted it might show collection already exists. 
        // and this issue might occur temperorily, periodic cache rebuild will keep cache up to date.

        if (!manager_->CreateCollection(name, size, distance, err)) {
            if(err.empty()) {
                err = "Failed to create collection, storage error.";
            }
            return false;
        }

        // update cache before returning success
        metadata_cache_.put(name, Metadata{size, distance, "active"});

        return true;
    }

    bool CollectionService::DeleteCollection(const std::string& name, std::string& err) {
        if (name.empty()) {
            err = "Invalid Collection name";
            return false;
        }

        if (!manager_->DeleteCollection(name, err)) {
            if(err.empty()) {
                err = "Failed to delete collection, storage error.";
            }
            return false;
        }

        // update cache before returning success
        metadata_cache_.remove(name);
        return true;
    }

    bool CollectionService::CheckCollectionExists(const std::string& name, std::string& err){
        if(name.empty()){
            err = "Invalid collection name format";
            return false;
        }

        // primary cache checking will be done, if collection status is not active, it checks disk storage
        Metadata result;
        if (metadata_cache_.get(name, result)) {
            if(result.status=="active"){
                // collection exists and active
                return true;
            }else{
                // check disk, to make sure pending collections are created or not
                if(!manager_->CollectionExists(name, err)){
                    return false;
                }
                return true;
            }
        }

        // collection does not exists in cache 
        // Note: during concurrent requests, it might  show temperorily wrong status
        return false;
    }

    bool CollectionService::LoadCollections(std::vector<zoro::utils::CollectionMetadata>& collections, std::string& err) {
        if(!manager_->LoadCollections(collections, err)){
            if(err==""){
                err="Unexpected error occured in storage system";
            }
            return false;
        }
        return true;
    }
    
    bool CollectionService::GetCollectionInfo(const std::string& name,std::vector<zoro::utils::CollectionInfoT>& collection, std::string& err){
        if(name.empty()){
            err = "Invalid collection name format";
            return false;
        }
        if(!manager_->GetCollection(name, collection, err)){
            if(err==""){
                err ="unexpected error occured to load collection info";
            }
            return false;
        }
        return true;
    }


    // deprecated, use GetCollectionInfo instead
    std::optional<zoro::utils::CollectionInfo>
    CollectionService::LoadCollection(const std::string& name, std::string& err) {
        auto result = manager_->LoadCollection(name);
        if (!result.has_value()) {
            err = "Collection not found.";
            return std::nullopt;
        }
        return result;
    }

    // deprecated, use LoadCollections instead
    std::vector<zoro::utils::CollectionInfo> CollectionService::ListCollections() const {
        return manager_->ListCollections();
    }

}

