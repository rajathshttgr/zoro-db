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
        int dimension=metaInfo.GetDimensions();
        std::string distance=metaInfo.GetDistance();

        // add validations in prev layer
        if(vectors.size()!=dimension) return false;

        // Append to WAL
        if (!wal_.log_upsert_point(coll_id, point_id, vectors, payload)) {
            return false;
        }

        if (FileUtils::CreateFileIfNotExists(coll_path + "/vectors.bin")) {

            std::ofstream ofs(
                coll_path + "/vectors.bin",
                std::ios::binary | std::ios::app
            );

            if (!ofs) return false;

            // 1. Write collection id (int)
            int32_t cid = coll_id;
            ofs.write(reinterpret_cast<const char*>(&cid), sizeof(cid));

            // 2. Write vector count
            uint32_t vec_count = static_cast<uint32_t>(vectors.size());
            ofs.write(reinterpret_cast<const char*>(&vec_count), sizeof(vec_count));

            // 3. Write raw float data
            ofs.write(reinterpret_cast<const char*>(vectors.data()),
                    vectors.size() * sizeof(float));

            return ofs.good();
        }

        return true;

        // vector binary entry format
        // [uint32 coll_id_length]
        // [coll_id bytes]
        // [uint32 vector_count]
        // [float][float][float]...

        // parse input
            // inputs collection_name, vectors, payload, point id
            // retrive collection info like dimension, points_count, collection id
        // append to wal
           // Optype is UpsertPoint, collection id, payload
        // store in database
            // store vector in vectors.bin along with point id
            // store payload in payload.bin and meta data in payload.idx
        // update meta
            // after success points count will incrrement in meta
        // acknowledge wal 
            // if everythinng successful ack wal, so no need to replay this entry
        // return sucess
            // all these thing done, then return true
        // return true;
    }

}