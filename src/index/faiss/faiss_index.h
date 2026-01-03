#pragma once

#include "../vector_index.h"
#include "faiss_config.h"
#include "faiss_id_map.h"

#include <memory>

namespace faiss{
    class Index;
};

class FaissIndex : public VectorIndex{
public:
    explicit FaissIndex(const FaissConfig& config);
    ~FaissIndex() override;

    void build(const std::vector<float>& vectors,
               const std::vector<uint64_t>& point_ids) override;

    void add(const float* vector, uint64_t point_id) override;
    void remove(uint64_t point_id) override;

    SearchResult search(const float* query,
                        uint32_t k) const override;

    size_t size() const override;


private:
    FaissConfig config_;
    std::unique_ptr<faiss::Index> index_;
    FaissIdMap id_map_; 
};