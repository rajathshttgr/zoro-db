#include "zoro_c_api.h"

#include "../../../services/include/CollectionService.h"
#include "../../../storage/include/StorageEngine.h"
#include "../../../collection/include/CollectionManager.h"
#include "../../../wal/include/wal_writer.h"
#include "../../../config.h"

#include <memory>
#include <cstring>

static std::unique_ptr<zoro::wal::WALWriter> g_wal;
static std::unique_ptr<zoro::storage::StorageEngine> g_storage;
static std::unique_ptr<zoro::core::CollectionManager> g_manager;
static std::unique_ptr<zoro::services::CollectionService> g_service;

extern "C" {

bool zoro_init(const char* data_path, char* err) {
    try {
        g_wal = std::make_unique<zoro::wal::WALWriter>(data_path);
        g_storage = std::make_unique<zoro::storage::StorageEngine>(data_path);
        g_manager = std::make_unique<zoro::core::CollectionManager>(data_path, g_storage.get(), *g_wal);
        g_service = std::make_unique<zoro::services::CollectionService>(g_manager.get());
        return true;
    } catch (const std::exception& e) {
        std::strcpy(err, e.what());
        return false;
    }
}

void zoro_shutdown() {
    g_service.reset();
    g_manager.reset();
    g_storage.reset();
}

bool zoro_create_collection(const char* name, int dimension, const char* distance, char* err) {
    std::string error;
    if (!g_service->CreateCollection(name, dimension, distance, error)) {
        std::strcpy(err, error.c_str());
        return false;
    }
    return true;
}

bool zoro_delete_collection(const char* name, char* err) {
    std::string error;
    if (!g_service->DeleteCollection(name, error)) {
        std::strcpy(err, error.c_str());
        return false;
    }
    return true;
}

bool zoro_list_collections(
    zoro_collection_info_t** out_collections,
    int* out_count,
    char* err
) {
    try {
        auto list = g_service->ListCollections();
        int count = static_cast<int>(list.size());

        auto* result = new zoro_collection_info_t[count];

        for (int i = 0; i < count; i++) {
            result[i].id = list[i].id;
            result[i].dimension = list[i].dimension;

            result[i].name = strdup(list[i].coll_name.c_str());
            result[i].distance = strdup(list[i].distance.c_str());
            result[i].status = strdup(list[i].status.c_str());
            result[i].created_at = strdup(list[i].created_at.c_str());
        }

        *out_collections = result;
        *out_count = count;
        return true;

    } catch (const std::exception& e) {
        std::strcpy(err, e.what());
        return false;
    }
}


void zoro_free_collections(
    zoro_collection_info_t* collections,
    int count
) {
    if (!collections) return;

    for (int i = 0; i < count; i++) {
        free((void*)collections[i].name);
        free((void*)collections[i].distance);
        free((void*)collections[i].status);
        free((void*)collections[i].created_at);
    }

    delete[] collections;
}


bool zoro_get_collection(
    const char* name,
    zoro_collection_info_t* out_info,
    char* err
) {
    std::string error;
    auto info = g_service->LoadCollection(name, error);

    if (!info) {
        std::strcpy(err, error.c_str());
        return false;
    }

    out_info->id = info->id;
    out_info->dimension = info->dimension;
    out_info->name = strdup(info->coll_name.c_str());
    out_info->distance = strdup(info->distance.c_str());
    out_info->status = strdup(info->status.c_str());
    out_info->created_at = strdup(info->created_at.c_str());

    return true;
}

void zoro_free_collection(zoro_collection_info_t* info) {
    if (!info) return;

    free((void*)info->name);
    free((void*)info->distance);
    free((void*)info->status);
    free((void*)info->created_at);
}

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
    char* err,
    size_t err_len
) {
    try {
        std::vector<int> ids;
        std::vector<std::vector<float>> vectors;
        std::vector<nlohmann::json> payloads;

        ids.reserve(point_count);
        vectors.reserve(point_count);
        payloads.reserve(point_count);


        for (size_t i = 0; i < point_count; ++i) {
            const zoro_point_t& p = points[i];

            ids.push_back(p.id);

            if (!p.vector || p.vector_len == 0) {
                throw std::runtime_error("empty vector");
            }

            vectors.emplace_back(
                p.vector,
                p.vector + p.vector_len
            );

            // payload (JSON)
            if (p.payload && std::strlen(p.payload) > 0) {
                payloads.emplace_back(
                    nlohmann::json::parse(p.payload)
                );
            } else {
                payloads.emplace_back(nlohmann::json::object());
            }
        }

        return g_service->UpsertPointsService(
            collection_name,
            ids,
            vectors,
            payloads
        );

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