#include "engine.hpp"
#include "storage.hpp"
#include "collection.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace zoro;
namespace fs=std::filesystem;

Engine::Engine(){
    zoroStorage::Initialize();
}

Engine::~Engine(){};

bool Engine::create_collection(const std::string& name, int dimension){

    if (!zoroStorage::CreateCollectionDir(name)) {
        std::cout << "[engine] Collection already exists. Skipping.\n";
    }

    collections.emplace(name, std::make_shared<Collection>(name, dimension));

    return true;

}

// bool Engine::has_collection(const std::string& name) const{
//     return collections.find(name)!=collections.end();
// }


// std::shared_ptr<Collection> Engine::get_collection(const std::string& name) const {
//     auto it=collections.find(name);
//     if(it==collections.end()){
//         return nullptr;
//     }
//     return it->second;  
// }
