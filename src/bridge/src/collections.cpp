#include "../zoro_c_api.h"
#include "internal_globals.h"
#include "../../services/src/CollectionService.h"
#include "../../utils/struct.h"
#include <vector>
#include <memory>
#include <cstring>
#include <string>


extern "C" {

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

bool zoro_check_collection_exists(const char* name, char* err) {
    std::string error;

    bool exists = g_service->CheckCollectionExists(name, error);

    if (!error.empty()) {
        std::strcpy(err, error.c_str());
        return false;
    }

    // Ensure empty string if no error
    err[0] = '\0';

    return exists;
}

bool zoro_list_collections(
    collection_metadata_t** out_collections,
    int* out_count,
    char* err
) {
    try {
        std::vector<zoro::utils::CollectionMetadata> list;
        std::string error;

        if (!g_service->ListCollections(list, error)) {
            std::strcpy(err, error.c_str());
            return false;
        }

        int count = static_cast<int>(list.size());
        auto* result = new collection_metadata_t[count];

        for (int i = 0; i < count; i++) {
            result[i].name = strdup(list[i].name.c_str());
            result[i].size = list[i].size;
            result[i].distance = strdup(list[i].distance.c_str());
            result[i].status = strdup(list[i].status.c_str());
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
    collection_metadata_t* collections,
    int count
) {
    if (!collections) return;

    for (int i = 0; i < count; i++) {
        free((void*)collections[i].name);
        free((void*)collections[i].distance);
        free((void*)collections[i].status);
    }

    delete[] collections;
}

// dev
bool zoro_get_collection(
    const char* name,
    zoro_collection_info_t* out_info,
    char* err
) {

    zoro::utils::CollectionInfo collection;
    std::string error;

    if (!g_service->GetCollectionInfo(name, collection, error)) {
        std::strcpy(err, error.c_str());
        return false;
    }

    out_info->id = collection.id;
    out_info->dimension = collection.size;;
    out_info->name = strdup(collection.name.c_str());
    out_info->distance = strdup(collection.distance.c_str());
    out_info->status = strdup(collection.status.c_str());
    out_info->created_at = strdup(collection.created_at.c_str());

    return true;
}

void zoro_free_collection(zoro_collection_info_t* info) {
    if (!info) return;

    free((void*)info->name);
    free((void*)info->distance);
    free((void*)info->status);
    free((void*)info->created_at);
}

}