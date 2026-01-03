#include "index_factory.h"
#include "faiss/faiss_index.h"

#include <stdexcept>

std::unique_ptr<VectorIndex>
IndexFactory::create_faiss_index(const FaissConfig& config)
{
    if (config.dimension == 0) {
        throw std::invalid_argument("Index dimension must be > 0");
    }

    return std::make_unique<FaissIndex>(config);
}
