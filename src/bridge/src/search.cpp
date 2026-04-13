#include "../zoro_c_api.h"
#include "internal_globals.h"
#include "../../services/src/CollectionService.h"
#include <vector>
#include <memory>
#include <cstring>
#include <string>


extern "C" {

bool zoro_search_points(
    const char* name,
    const float* vector,
    size_t vector_dim,
    int k,
    zoro_search_point_t** out_points,
    int* out_count,
    char* err
) {
    if (!name || !vector || !out_points || !out_count) {
        if (err) std::strcpy(err, "invalid argument");
        return false;
    }

    try {
        std::vector<float> query_vector(vector, vector + vector_dim);
        std::string error;

        auto results = g_service->SearchPointByVector(
            name,
            query_vector,
            k,
            error
        );

        if (!error.empty()) {
            if (err) std::strcpy(err, error.c_str());
            return false;
        }

        int count = static_cast<int>(results.size());
        zoro_search_point_t* points =
            static_cast<zoro_search_point_t*>(
                std::calloc(count, sizeof(zoro_search_point_t))
            );

        for (int i = 0; i < count; ++i) {
            points[i].point_id = results[i].point_id;
            points[i].score = results[i].score;

            std::string payload_str = results[i].payload.dump();
            char* payload_cstr =
                static_cast<char*>(std::malloc(payload_str.size() + 1));

            std::memcpy(payload_cstr, payload_str.c_str(), payload_str.size() + 1);
            points[i].payload = payload_cstr;
        }

        *out_points = points;
        *out_count = count;
        return true;
    }
    catch (const std::exception& e) {
        if (err) std::strcpy(err, e.what());
        return false;
    }
}

void zoro_free_search_result(
    zoro_search_point_t* points,
    int count
) {
    if (!points) return;

    for (int i = 0; i < count; ++i) {
        std::free((void*)points[i].payload);
    }
    std::free(points);
}


bool zoro_scroll_points(
    const char* name,
    int k,
    zoro_scroll_point_t** out_points,
    int* out_count,
    char* err
) {
    if (!name || !out_points || !out_count) {
        if (err) std::strcpy(err, "invalid argument");
        return false;
    }

    try {
        std::string error;
        
        auto results = g_service->ScrollPointMetadata(
            name,
            k,
            error
        );

        if (!error.empty()) {
            if (err) std::strcpy(err, error.c_str());
            return false;
        }

        int count = static_cast<int>(results.size());
        zoro_scroll_point_t* points =
            static_cast<zoro_scroll_point_t*>(
                std::calloc(count, sizeof(zoro_scroll_point_t))
            );

        for (int i = 0; i < count; ++i) {
            points[i].point_id = results[i].point_id;

            std::string payload_str = results[i].payload.dump();
            char* payload_cstr =
                static_cast<char*>(std::malloc(payload_str.size() + 1));

            std::memcpy(payload_cstr, payload_str.c_str(), payload_str.size() + 1);
            points[i].payload = payload_cstr;
        }

        *out_points = points;
        *out_count = count;
        return true;
    }
    catch (const std::exception& e) {
        if (err) std::strcpy(err, e.what());
        return false;
    }
}


void zoro_free_scroll_result(
    zoro_scroll_point_t* points,
    int count
) {
    if (!points) return;

    for (int i = 0; i < count; ++i) {
        std::free((void*)points[i].payload);
    }
    std::free(points);
}

}