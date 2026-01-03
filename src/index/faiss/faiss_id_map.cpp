#include "faiss_id_map.h"

#include <stdexcept>

void FaissIdMap::add(uint64_t point_id){

    // FAISS assigns internal IDs sequentially
    uint64_t internal_id = internal_to_point_.size();

    internal_to_point_.push_back(point_id);
    point_to_internal_[point_id] = internal_id;
}

uint64_t FaissIdMap::get_point_id(uint64_t faiss_internal_id) const
{
    if (faiss_internal_id >= internal_to_point_.size()) {
        throw std::out_of_range("Invalid FAISS internal id");
    }

    return internal_to_point_[faiss_internal_id];
}

void FaissIdMap::mark_deleted(uint64_t point_id)
{
    auto it = point_to_internal_.find(point_id);
    if (it == point_to_internal_.end()) {
        return; // already deleted or never existed
    }

    uint64_t internal_id = it->second;

    // Mark deletion by invalidating mapping
    internal_to_point_[internal_id] = 0; // 0 is reserved as invalid

    point_to_internal_.erase(it);
}

bool FaissIdMap::is_deleted(uint64_t point_id) const
{
    return point_to_internal_.find(point_id) == point_to_internal_.end();
}


size_t FaissIdMap::size() const
{
    return point_to_internal_.size();
}