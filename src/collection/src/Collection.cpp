#include "../include/Collection.h"

namespace zoro::core{
Collection::Collection(std::string name,int dim): name_(std::move(name)),dim_(dim){}
}