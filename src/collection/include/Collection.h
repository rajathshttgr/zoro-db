#pragma once
#include <string>

namespace zoro::core{

class Collection{
public:
    Collection(std::string name,int dim);

    const std::string& name() const{return name_;}
    int dimension() const {return dim_;}
    
private:
    std::string name_;
    int dim_;
};
}