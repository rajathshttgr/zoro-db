#pragma once
#include <memory>
#include <string>
#include "../../index/vector_index.h"

namespace zoro::core {

struct CollectionRuntime {
    std::unique_ptr<VectorIndex> index;
    int dimension;
};

}
