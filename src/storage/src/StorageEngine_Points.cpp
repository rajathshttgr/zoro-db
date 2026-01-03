#include "StorageEngine.h"
#include "CollectionMeta.h"
#include "FileUtils.h"

namespace zoro::storage {

    bool StorageEngine::UpsertPoints(const std::string &coll_name, int point_id, const std::vector<float> &vectors, const json& payload){

        if(!StorageEngine::CollectionExists(coll_name)){
            return false;
        }

        std::string coll_path=collection_root_+"/"+coll_name;
        CollectionMeta metaInfo(coll_path);
        int coll_id=metaInfo.GetCollectionId();

        // Append to WAL 
        if (!wal_.log_upsert_point(coll_id, point_id, vectors, payload)) {
            return false;
        }

        // vectors.bin // [length][data]...
        // vectors.idx vector(file, id, offset, length, is_deleted)
        // payload.bin // [length][data]...
        // payload.idx payload(file, id, offset, length, is_deleted)

        // vector upsert logic // append(file,data)
        uint64_t offset = FileUtils::appendBinaryData(coll_path+"/vectors.bin", reinterpret_cast<const char*>(vectors.data()), vectors.size() * sizeof(float));
        if(!FileUtils::updateIndexFile(coll_path+"/vectors.idx", point_id, offset, vectors.size() * sizeof(float), 1)) {
            return false;
        }

        // payload upsert logic // append (file,data)
        std::string payload_str = payload.dump();
        uint64_t payload_offset = FileUtils::appendBinaryData(coll_path+"/payload.bin", payload_str.data(), payload_str.size());
        if(!FileUtils::updateIndexFile(coll_path+"/payload.idx", point_id, payload_offset, payload_str.size(), 1)) {
            return false;
        }

        metaInfo.IncrementPointsCount(); 


        // FAISS index update can be added here

        return true;

    }


    bool StorageEngine::DeletePoints(const std::string &coll_name, int point_id){

        if(!StorageEngine::CollectionExists(coll_name)){
            return false;
        }

        std::string coll_path=collection_root_+"/"+coll_name;
        CollectionMeta metaInfo(coll_path);
        int coll_id=metaInfo.GetCollectionId();

        // Append to WAL
        if (!wal_.log_delete_point(coll_id, point_id)) {
            return false;
        }
        

        if(!FileUtils::updateIndexFile(coll_path+"/vectors.idx", point_id, std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint32_t>::max(), 0)) {
            return false;
        }

        if(!FileUtils::updateIndexFile(coll_path+"/payload.idx", point_id,std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint32_t>::max(), 0)) {
            return false;
        }

        metaInfo.DecrementPointsCount();

        return true;
    }


    int StorageEngine::CountPoints(const std::string &coll_name){
        if(!StorageEngine::CollectionExists(coll_name)){
            return false;
        }
        std::string coll_path=collection_root_+"/"+coll_name;
        CollectionMeta metaInfo(coll_path);
        int points_count=metaInfo.GetPointsCount();
        return points_count;
    }

}