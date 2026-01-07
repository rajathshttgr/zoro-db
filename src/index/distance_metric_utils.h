#pragma once
#include <string>
#include "faiss/faiss_config.h"

inline DistanceMetric DistanceMetricFromString(const std::string& dist) {
    if (dist == "l2" || dist == "L2") {
        return DistanceMetric::L2;
    }
    if (dist == "cosine" || dist == "COSINE") {
        return DistanceMetric::COSINE;
    }
    if (dist == "dot" || dist == "DOT") {
        return DistanceMetric::DOT;
    }
    throw std::invalid_argument("Unknown distance metric: " + dist);
}
