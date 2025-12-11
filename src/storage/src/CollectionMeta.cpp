#include "CollectionMeta.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace zoro::storage{

CollectionMeta::CollectionMeta(const std::string& collection_path):meta_path_(collection_path+"/meta.json"){}

void CollectionMeta::InitDefault(){
    nlohmann::json j;
    j["dimensions"]=128;

    std::ofstream out(meta_path_);
    out<<j.dump(4);
}

int CollectionMeta::GetDimensions() const{
    std::ifstream in(meta_path_);
    nlohmann::json j;
    in>>j;
    return j["dimensions"];
}

void CollectionMeta::SetDimensions(int dim){
    nlohmann::json j;
    j["dimensions"]=dim;
    std::ofstream(meta_path_)<<j.dump(4);
}
}