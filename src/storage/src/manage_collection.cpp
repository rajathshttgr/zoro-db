#include "StorageEngine.h"
#include "Catalog.h"
#include "CollectionMeta.h"
#include "FileUtils.h"
#include "Distance_utils.h"
#include <filesystem>
#include <vector>
#include <cstdint>
#include <cstring> 
#include "../../utils/common/generate_id.h"

namespace fs=std::filesystem;

namespace zoro::storage {

bool StorageEngine::CreateCollection(const std::string& collection_name, int dimension, std::string distance, std::string& err) {

    // random id to avoid collision
    std::string random_id = std::string("__temp_") + generateId(); 

    // temp_dir is used to ensure that if the process crashes during collection creation, we don't end up with a partially created collection directory.
    std::string temp_dir = collection_root_ + "/"+ random_id + collection_name; 

    std::string target_dir = collection_root_ + "/" + collection_name;

    try
    {
        fs::create_directories(temp_dir);

        // initialize wal under temp_dir

        // initialize metdata with status creating

        CollectionMeta meta(temp_dir);
        meta.InitDefault(dimension, distance, collection_name);

        // build collection - segments, meta etc
        fs::create_directories(temp_dir+"/segments");
        fs::create_directories(temp_dir+"/wal");

        // commit metadata
        meta.SetStatus("active"); 

        // commit wal acknowledgement

        if(fs::exists(target_dir)){
            throw std::runtime_error("Collection already exists");
        }
        fs::rename(temp_dir, target_dir);
        return true;
    }
    catch(const std::exception& e)
    {
        err = e.what();
        return false;
    }
    
}

// CREATE COLLECTION - STORAGE
// - create a temp directory
// - initialize wal under temp_dir
// - initialize metdata with status creating
// - build collection - segments, meta etc
// - update meta file status as active
// - commit wal acknowledgement (optional)
// - rename temp directory to final collection name
// - return succes

bool StorageEngine::DeleteCollection(const std::string& collection_name, std::string& err){

    std::string target_dir = collection_root_+"/"+collection_name;
    CollectionMeta meta(target_dir);

    // commit metadata
    meta.SetStatus("deleting"); 

    //this cannot be undone
    fs::remove_all(target_dir);

    try
    {
        if(fs::exists(target_dir)){
            // this cannot be undone
            // TODO Disc: do we need to archive or hard delete?
            fs::remove_all(target_dir);
        }
        return true;
    }
    catch(const std::exception& e)
    {
        err = e.what();
        return false;
    }

}

}
