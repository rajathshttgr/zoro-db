#include "Catalog.h"
#include "Utils.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace zoro::storage{

using json = nlohmann::json;

Catalog::Catalog(const std::string& root):path_(root+"/catalog.json"){
    if (!std::filesystem::exists(path_) || std::filesystem::file_size(path_) == 0)
    {
        json j;
        j["current_coll_id"] = 100;
        j["collections"] = json::object();

        std::ofstream out(path_);
        out << j.dump(4);
    }
}

bool Catalog::AddCollection(const std::string& name, int& out_coll_id)
{
    std::ifstream in(path_);
    nlohmann::json j;
    in >> j;
    in.close();

    auto& collections = j["collections"];

    if (collections.contains(name))
        return false;

    int curr_id = j["current_coll_id"];

    collections[name] = {
        { "id", curr_id },
        { "created_at", CurrentTimestampUTC() }
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
    std::ifstream in(path_);
    nlohmann::json j;
    in >> j;

    return j["collections"].contains(name);
}

std::vector<std::string> Catalog::ListCollections() const
{
    std::ifstream in(path_);
    nlohmann::json j;
    in >> j;

    std::vector<std::string> names;
    for (auto& el : j["collections"].items()) {
        names.push_back(el.key());
    }
    return names;
}


}


