#include "CollectionMeta.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>

namespace zoro::storage{

CollectionMeta::CollectionMeta(const std::string& collection_path):meta_path_(collection_path+"/meta.json"){}

void CollectionMeta::InitDefault(int dim, std::string dist,std::string collection_name){
    nlohmann::json j;
    j["dimensions"]=dim;
    j["distance"]=dist;
    j["coll_id"]=999;
    j["coll_name"]=collection_name;
    j["points_count"]=0;
    j["status"]="pending";

    std::ofstream out(meta_path_);
    out<<j.dump(4);
}

void CollectionMeta::SetStatus(const std::string& status){
    nlohmann::json j;
    std::ifstream in(meta_path_);
    if (in.good()) {
        in >> j;
    }
    in.close();

    j["status"] = status;

    std::ofstream out(meta_path_);
    out << j.dump(4);
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

int CollectionMeta::GetPointsCount() const{
    std::ifstream in(meta_path_);
    nlohmann::json j;
    in>>j;
    return j["points_count"];
}

// void CollectionMeta::IncrementPointsCount(int count){
//     nlohmann::json j;
//     std::ifstream in(meta_path_);
//     if (!in.is_open()) return;
//     in >> j;
//     in.close();

//      j["points_count"] = j.value("points_count", 0) + count;

//     std::ofstream out(meta_path_);
//     out << j.dump(4);
// }

void CollectionMeta::IncrementPointsCount(int count){
    int fd = open(meta_path_.c_str(), O_RDWR);
    if (fd == -1) return;

    // Acquire exclusive lock (blocks until available)
    flock(fd, LOCK_EX);

    // Read JSON
    std::ifstream in(meta_path_);
    nlohmann::json j;
    if (in.good()) {
        in >> j;
    }
    in.close();

    // Modify
    j["points_count"] = j.value("points_count", 0) + count;

    // Write back
    std::ofstream out(meta_path_);
    out << j.dump(4);
    out.close();

    // Release lock
    flock(fd, LOCK_UN);
    close(fd);
}

void CollectionMeta::DecrementPointsCount(int count){
    nlohmann::json j;
    std::ifstream in(meta_path_);
    if (!in.is_open()) return;
    in >> j;
    in.close();

     j["points_count"] = j.value("points_count", 0) - count;

    std::ofstream out(meta_path_);
    out << j.dump(4);
}

}