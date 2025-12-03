#include "collection.hpp"
#include <algorithm>

using namespace zoro;

Collection::Collection(const std::string& name, int dimension): name_(name), dim_(dimension) {};
Collection::~Collection() {};

bool Collection::insert(const Vector& v){
    if((int)v.values.size() != dim_){
        return false;
    }
    std::lock_guard<std::mutex> lock(mu_);
    storage_[v.id]=v.values;
    return true;
}

bool Collection::get(const std::string& id, Vector& out) const{
    std::lock_guard<std::mutex> lock(mu_);
    auto it=storage_.find(id);
    if(it==storage_.end()){
        return false;
    }
    out.id=it->first;
    out.values=it->second;
    return true;
}

size_t Collection::size() const{
    std::lock_guard<std::mutex> lock(mu_);
    return storage_.size();
}

int Collection::dimension() const{
    return dim_;
}

const std::string& Collection::name() const{
    return name_;
}