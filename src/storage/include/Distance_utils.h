#pragma once
#include <string>
#include <stdexcept>
#include <algorithm>
#include "../../wal/include/types.h"

inline DistType DistTypeFromString(std::string dist) {
    // normalize
    std::transform(dist.begin(), dist.end(), dist.begin(), ::tolower);

    if (dist == "euclid") return DistType::EUCLID;
    if (dist == "cosine") return DistType::COSINE;
    if (dist == "dot") return DistType::DOT;

    throw std::invalid_argument("Unsupported distance type");
}

// map dist types
inline std::string DistTypeToString(DistType type) {
    switch (type) {
        case DistType::EUCLID: return "EUCLID";
        case DistType::COSINE: return "COSINE";
        case DistType::DOT:    return "DOT";
    }
    return "UNKNOWN";
}
