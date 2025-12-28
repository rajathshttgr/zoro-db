#include "StorageEngine.h"
#include <nlohmann/json.hpp>

namespace zoro::storage {

    bool StorageEngine::UpsertPoints(const std::string coll_name){

        if(!StorageEngine::CollectionExists(coll_name)){
            return false;
        }

        return true;


        // std::string distance=metaInfo.distance;
        // int dimension=metaInfo.dimension;
        // int points_count=metaInfo.points_count;

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