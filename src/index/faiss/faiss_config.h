#pragma once

#include <cstdint>

enum class DistanceMetric {
    L2,
    COSINE,
    DOT
};


struct FaissConfig {
    uint32_t dimension;
    DistanceMetric metric;
};

