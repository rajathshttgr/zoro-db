#include "faiss_index.h"

#include <faiss/IndexFlat.h>
#include <faiss/Index.h>

#include <stdexcept>
#include <cassert>
#include <algorithm>

// constructor
FaissIndex::FaissIndex(const FaissConfig& config):config_(config){

    // following things are already validated in upper layers, it ensures last step validations

    if(config_.dimension==0){
        throw std::invalid_argument("FAISS dimension must be > 0");
    }

    // Initialize FAISS index based on distance metric
    switch (config_.metric)
    {
    case DistanceMetric::L2:
        index_ = std::make_unique<faiss::IndexFlatL2>(config_.dimension);
        break;

    case DistanceMetric::DOT:
    case DistanceMetric::COSINE:
        // cosine similarity = normalized dot product
        index_ = std::make_unique<faiss::IndexFlatIP>(config_.dimension);
        break;
    
    default:
        throw std::invalid_argument("Unsupported distance metric");
    }
}

// destructor
FaissIndex::~FaissIndex() = default;

// build or startup

void FaissIndex::build(const std::vector<float>& vectors,
                       const std::vector<uint64_t>& point_ids)
{
    if (vectors.empty()) {
        return; // empty collection
    }

    if (point_ids.empty()) {
        throw std::invalid_argument("point_ids cannot be empty when vectors exist");
    }

    if (vectors.size() % config_.dimension != 0) {
        throw std::invalid_argument("Vector data size is not divisible by dimension");
    }

    size_t num_vectors = vectors.size() / config_.dimension;

    if (num_vectors != point_ids.size()) {
        throw std::invalid_argument("Mismatch between vectors and point_ids count");
    }

    // Reset index (rebuild scenario)
    index_->reset();
    id_map_.clear();

    // Add vectors to FAISS
    index_->add(num_vectors, vectors.data());

    // Build internal ID → point_id mapping
    for (uint64_t pid : point_ids) {
        id_map_.add(pid);
    }


}


void FaissIndex::add(const float* vector, uint64_t point_id)
{
    assert(vector != nullptr);

    // Add vector to FAISS (1 vector)
    index_->add(1, vector);

    // Track mapping
    id_map_.add(point_id);
}


void FaissIndex::remove(uint64_t point_id)
{
    // Logical delete only
    id_map_.mark_deleted(point_id);
}


SearchResult FaissIndex::search(const float* query, uint32_t k) const
{
    assert(query != nullptr);

    SearchResult result;

    if (index_->ntotal == 0 || k == 0) {
        return result;
    }

    if (k > static_cast<uint32_t>(index_->ntotal)) {
        k = static_cast<uint32_t>(index_->ntotal);
    }

    // FAISS returns internal IDs
    uint32_t search_k = std::min<uint32_t>(
        k * 2,
        static_cast<uint32_t>(index_->ntotal)
    );
    
    std::vector<faiss::idx_t> labels(search_k);
    std::vector<float> distances(search_k);
    
    index_->search(1, query, search_k, distances.data(), labels.data());

    // Convert internal IDs → point_ids
    for (uint32_t i = 0; i < search_k && result.point_ids.size() < k; ++i) {
        faiss::idx_t internal_id = labels[i];

        if (internal_id < 0) {
            continue; // FAISS uses -1 for invalid
        }

        uint64_t point_id = id_map_.get_point_id(static_cast<uint64_t>(internal_id));

        if (id_map_.is_deleted(point_id)) {
            continue;
        }

        result.point_ids.push_back(point_id);
        result.distances.push_back(distances[i]);
    }

    return result;

}


size_t FaissIndex::size() const
{
    return static_cast<size_t>(index_->ntotal);
}