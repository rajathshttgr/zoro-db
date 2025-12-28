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
        g_storage = std::make_unique<zoro::storage::StorageEngine>(data_path, *g_wal);
        g_manager = std::make_unique<zoro::core::CollectionManager>(g_storage.get());
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


}
