#pragma once

#include <memory>
#include "vector_index.h"
#include "faiss/faiss_config.h"

class IndexFactory {
public:
    static std::unique_ptr<VectorIndex>
    create_faiss_index(const FaissConfig& config);
};
