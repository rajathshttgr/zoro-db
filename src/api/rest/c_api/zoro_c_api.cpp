#include "zoro_c_api.h"

#include "../../CollectionService.h"
#include "../../../storage/include/StorageEngine.h"
#include "../../../collection/include/CollectionManager.h"
#include "../../../config.h"

#include <memory>
#include <cstring>

static std::unique_ptr<zoro::storage::StorageEngine> g_storage;
static std::unique_ptr<zoro::core::CollectionManager> g_manager;
static std::unique_ptr<zoro::api::CollectionService> g_service;

extern "C" {

bool zoro_init(const char* data_path, char* err) {
    try {
        g_storage = std::make_unique<zoro::storage::StorageEngine>(data_path);
        g_manager = std::make_unique<zoro::core::CollectionManager>(g_storage.get());
        g_service = std::make_unique<zoro::api::CollectionService>(g_manager.get());
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

bool zoro_create_collection(const char* name, int dimension, char* err) {
    std::string error;
    if (!g_service->CreateCollection(name, dimension, error)) {
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

}
