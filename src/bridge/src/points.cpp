#include "../zoro_c_api.h"
#include "internal_globals.h"
#include "../../services/src/CollectionService.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <memory>
#include <cstring>
#include <string>
#include "../../utils/struct.h"


extern "C" {

int zoro_count_points(const char* name, char* err){
    try {
        int count = g_service->CountPointsService(name);
        return count;
    } catch (const std::exception& e) {
        std::strcpy(err, e.what());
        return -1;
    }
}

bool zoro_upsert_points(
    const char* collection_name,
    const zoro_point_t* points,
    size_t point_count,  
    int* operation_id,
    char* err,
    size_t err_len
) {
    try {
        if (!operation_id) return false;
        std::vector<zoro::utils::Points> pts;
        pts.reserve(point_count);
        
        for (size_t i = 0; i < point_count; ++i) {
            const zoro_point_t& p = points[i];

            zoro::utils::Points point;

            point.id = p.id;

            point.vectors = std::vector<float>(
                p.vector,
                p.vector + p.vector_len
            );

            if (p.payload && std::strlen(p.payload) > 0) {
                point.payload = nlohmann::json::parse(p.payload);
            } else {
                point.payload = nlohmann::json::object();
            }

            pts.emplace_back(std::move(point));
        }

        std::string error_msg;
        bool result = g_service->UpsertPointsService(
            collection_name,
            std::move(pts),
            *operation_id,
            error_msg
        );

        if (!result && err && err_len > 0) {
            std::strncpy(err, error_msg.c_str(), err_len - 1);
            err[err_len - 1] = '\0';
        }

        return result;

    }catch (const std::exception& e) {
        if (err && err_len > 0) {
            strncpy(err, e.what(), err_len - 1);
            err[err_len - 1] = '\0';
        }
        return false;
    }
}

bool zoro_delete_points(
    const char* collection_name,
    const int* point_ids,
    size_t point_count,  
    char* err,
    size_t err_len
) {
    try {
        std::vector<int> ids;
        ids.reserve(point_count);

        for (size_t i = 0; i < point_count; ++i) {
            ids.push_back(point_ids[i]);
        }

        return g_service->DeletePointsService(
            collection_name,
            ids
        );

    }catch (const std::exception& e) {
        if (err && err_len > 0) {
            strncpy(err, e.what(), err_len - 1);
            err[err_len - 1] = '\0';
        }
        return false;
    }
}


bool zoro_point_retrival(
    const char* name,
    const int* point_id,
    zoro_point_retrival_t* out_info,
    char* err
){
    std::string error;

    auto info = g_service->RetrivePointById(name, *point_id, error);

    if (!info) {
        std::strcpy(err, error.c_str());
        return false;
    }

    out_info->status   = strdup(info->status.c_str());
    out_info->point_id = info->point_id;
    out_info->payload  = strdup(info->payload.dump().c_str());

    return true;
}

void zoro_free_point_retrival(zoro_point_retrival_t* info){
    if (!info) return;

    free((void*)info->status);
    free((void*)info->payload);
}

}