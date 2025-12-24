#include "CollectionMeta.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace zoro::storage{

CollectionMeta::CollectionMeta(const std::string& collection_path):meta_path_(collection_path+"/meta.json"){}

void CollectionMeta::InitDefault(int dim, std::string dist,int coll_id, std::string collection_name){
    nlohmann::json j;
    j["dimensions"]=dim;
    j["distance"]=dist;
    j["coll_id"]=coll_id;
    j["coll_name"]=collection_name;

    std::ofstream out(meta_path_);
    out<<j.dump(4);
}

int CollectionMeta::GetDimensions() const{
    std::ifstream in(meta_path_);
    nlohmann::json j;
    in>>j;
    return j["dimensions"];
}

std::string CollectionMeta::GetDistance() const {
    std::ifstream in(meta_path_);
    nlohmann::json j;
    in >> j;
    return j.value("distance", "COSINE");
}

int CollectionMeta::GetCollectionId() const {
    std::ifstream in(meta_path_);
    nlohmann::json j;
    in >> j;
    return j.value("coll_id", -1);
}

void CollectionMeta::SetDimensions(int dim){
    nlohmann::json j;
    std::ifstream in(meta_path_);
    if (in.good()) {
        in >> j;
    }
    in.close();

    j["dimensions"] = dim;

    std::ofstream out(meta_path_);
    out << j.dump(4);
}
}