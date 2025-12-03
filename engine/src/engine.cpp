#include "engine.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace zoro;
namespace fs=std::filesystem;

Engine::Engine(const std::string& data_dir): data_dir_(data_dir){
    try{
        if(!fs::exists(data_dir_)){
            fs::create_directories(data_dir_);
        }
    }catch(const fs::filesystem_error& e){
        std::cerr<<"[Engine] Failed to create data directory: "<<e.what()<<std::endl;
    }
}

Engine::~Engine(){};

bool Engine::create_collection(const std::string& name, int dimension){
    if(collections_.find(name)!=collections_.end()){
        return false;
    }

    fs::path collection_path=fs::path(data_dir_) / "collections" / name;
    try{
        if(!fs::exists(collection_path)){
            fs::create_directories(collection_path);
        }
    }catch(const std::exception& e){
        std::cerr<<"[Engine] Failed to create collection directory: "<<e.what()<<std::endl;
        return false;
    }

    auto col=std::make_shared<Collection>(name, dimension);
    collections_[name]=col;
    return true;

}


bool Engine::has_collection(const std::string& name) const{
    return collections_.find(name)!=collections_.end();
}


std::shared_ptr<Collection> Engine::get_collection(const std::string& name) const {
    auto it=collections_.find(name);
    if(it==collections_.end()){
        return nullptr;
    }
    return it->second;  
}
