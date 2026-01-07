#include "StorageEngine.h"
#include "CollectionMeta.h"
#include "FileUtils.h"

namespace zoro::storage {

    bool StorageEngine::UpsertPoints(const std::string &coll_name, int point_id, const std::vector<float> &vectors, const json& payload){

        std::string coll_path=collection_root_+"/"+coll_name;
        CollectionMeta metaInfo(coll_path);

        // vectors.bin // [length][data]...
        // vectors.idx vector(file, id, offset, length, is_deleted)
        // payload.bin // [length][data]...
        // payload.idx payload(file, id, offset, length, is_deleted)

        // vector upsert logic // append(file,data)
        uint64_t offset = FileUtils::appendBinaryData(coll_path+"/vectors.bin", reinterpret_cast<const char*>(vectors.data()), vectors.size() * sizeof(float));
        auto vec_result = FileUtils::updateIndexFile(coll_path+"/vectors.idx", point_id, offset, vectors.size() * sizeof(float), 1);

        if(vec_result == IndexUpdateResult::NoOp) {
            return false;
        }

        // payload upsert logic // append (file,data)
        std::string payload_str = payload.dump();
        uint64_t payload_offset = FileUtils::appendBinaryData(coll_path+"/payload.bin", payload_str.data(), payload_str.size());
        auto payload_result = FileUtils::updateIndexFile(coll_path+"/payload.idx", point_id, payload_offset, payload_str.size(), 1);
        if(payload_result == IndexUpdateResult::NoOp) {
            return false;
        }

        if (vec_result == IndexUpdateResult::Inserted) {
            metaInfo.IncrementPointsCount(1);
        }

        return true;

    }


    bool StorageEngine::DeletePoints(const std::string &coll_name, int point_id){

        std::string coll_path=collection_root_+"/"+coll_name;
        CollectionMeta metaInfo(coll_path);

        auto vec_result = FileUtils::updateIndexFile(coll_path+"/vectors.idx", point_id, std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint32_t>::max(), 0);
        if(vec_result == IndexUpdateResult::NoOp) {
            return false;
        }

        auto payload_result = FileUtils::updateIndexFile(coll_path+"/payload.idx", point_id, std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint32_t>::max(), 0);
        if(payload_result == IndexUpdateResult::NoOp) {
            // Rollback vector deletion if payload deletion fails
            FileUtils::updateIndexFile(coll_path+"/vectors.idx", point_id, std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint32_t>::max(), 1);
            return false;
        }

        if (vec_result == IndexUpdateResult::Updated) {
            metaInfo.DecrementPointsCount(1);
        }

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