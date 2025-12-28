#include "Catalog.h"
#include "Utils.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace zoro::storage{

using json = nlohmann::json;

Catalog::Catalog(const std::string& root):path_(root+"/catalog.json"){

    std::filesystem::create_directories(root); 

    if (!std::filesystem::exists(path_) || std::filesystem::file_size(path_) == 0)
    {
        json j;
        j["current_coll_id"] = 100;
        j["collections"] = json::object();

        std::ofstream out(path_);
        out << j.dump(4);
    }
}

bool Catalog::AddCollection(const std::string& name, int& out_coll_id, int& dimension, std::string& distance)
{
    std::ifstream in(path_);
    nlohmann::json j;
    in >> j;
    in.close();

    auto& collections = j["collections"];

    if (collections.contains(name))
        return false;

    if(name.length()==0)
        return false;

    if(dimension<1 || dimension>9999)
        return false;

    int curr_id = j["current_coll_id"];

    collections[name] = {
        { "id", curr_id },
        { "dimension",dimension},
        { "distance",distance},
        { "created_at", CurrentTimestampUTC() },
        { "status", "active"} // demo status
    };

    out_coll_id = curr_id;
    j["current_coll_id"] = curr_id + 1;

    std::ofstream out(path_);
    out << j.dump(4);
    return true;
}

bool Catalog::RemoveCollection(const std::string& name)
{
    std::ifstream in(path_);
    nlohmann::json j;
    in >> j;
    in.close();

    auto& collections = j["collections"];

    if (!collections.contains(name))
        return false;

    collections.erase(name);

    std::ofstream out(path_);
    out << j.dump(4);
    return true;
}

bool Catalog::CollectionExists(const std::string& name) const
{
    if (!std::filesystem::exists(path_) || std::filesystem::file_size(path_) == 0)
        return false;

    std::ifstream in(path_);
    nlohmann::json j;
    in >> j;

    return j["collections"].contains(name);
}

int Catalog::GetCollectionId(const std::string& name){
    std::ifstream in(path_);
    json j;
    in >> j;

    const auto& collections = j["collections"];

    if (!collections.contains(name))
        return -1;

    const auto& c = collections[name];

    return c.at("id").get<int>();
}

std::optional<CollectionInfo> Catalog::GetCollectionInfo(const std::string& name) const{
    std::ifstream in(path_);
    json j;
    in >> j;

    const auto& collections = j["collections"];

    if (!collections.contains(name))
        return std::nullopt;

    const auto& c = collections[name];

    CollectionInfo info;
    info.coll_name = name;
    info.id = c.at("id").get<int>();
    info.dimension = c.at("dimension").get<int>();
    info.distance = c.at("distance").get<std::string>();
    info.status = c.at("status").get<std::string>();
    info.created_at = c.at("created_at").get<std::string>();

    return info;
}


std::vector<CollectionInfo> Catalog::ListCollections() const
{
    std::ifstream in(path_);
    json j;
    in >> j;

    const auto& collections = j["collections"];

    std::vector<CollectionInfo> collection_list;
    collection_list.reserve(collections.size());

    for (const auto& [name, c] : collections.items()) {
        CollectionInfo info;
        info.coll_name = name;
        info.id = c.at("id").get<int>();
        info.dimension = c.at("dimension").get<int>();
        info.distance = c.at("distance").get<std::string>();
        info.status = c.at("status").get<std::string>();
        info.created_at = c.at("created_at").get<std::string>();

        collection_list.push_back(std::move(info));
    }

    return collection_list;
}


}


