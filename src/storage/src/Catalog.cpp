#include "Catalog.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace zoro::storage{

Catalog::Catalog(const std::string& root):path_(root+"/catalog.json"){
    if (!std::filesystem::exists(path_) || std::filesystem::file_size(path_) == 0)
    {
        nlohmann::json j = nlohmann::json::object();

        std::ofstream out(path_);
        out << j.dump(4);     
    }
}

bool Catalog::AddCollection(const std::string& name, const std::string& collection_path){
    std::ifstream in(path_);
    nlohmann::json j;
    in>>j;

    if(j.contains(name)) return false;
    j[name]={collection_path};

    std::ofstream out(path_);
    out<<j.dump(4);
    return true;
}

bool Catalog::RemoveCollection(const std::string& name){
    std::ifstream in(path_);
    nlohmann::json j;
    in>>j;

    if(!j.contains(name)) return false;
    j.erase(name);

    std::ofstream out(path_);
    out<<j.dump(4);
    return true;
}

std::vector<std::string> Catalog::ListCollections() const{
    std::ifstream in(path_);
    nlohmann::json j;
    in>>j;

    std::vector<std::string> names;
    for(auto& el: j.items()){
        names.push_back(el.key());
    }
    return names;
}
}


