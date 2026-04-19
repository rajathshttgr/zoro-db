#include "../zoro_c_api.h"
#include "internal_globals.h"

#include "../../services/src/CollectionService.h"
#include "../../storage/include/StorageEngine.h"
#include "../../collection/src/CollectionManager.h"
#include "../../wal/include/wal_writer.h"
#include "../../config.h"

#include <memory>
#include <cstring>
#include <string>


std::unique_ptr<zoro::wal::WALWriter> g_wal;
std::unique_ptr<zoro::storage::StorageEngine> g_storage;
std::unique_ptr<zoro::core::CollectionManager> g_manager;
std::unique_ptr<zoro::services::CollectionService> g_service;

extern "C" {


bool zoro_init(const char* data_path, char* err) {
    try {
        g_storage = std::make_unique<zoro::storage::StorageEngine>(data_path);
        g_manager = std::make_unique<zoro::core::CollectionManager>(data_path, g_storage.get());
        g_service = std::make_unique<zoro::services::CollectionService>(g_manager.get());
        std::string error;
        if(!g_service->InitStartUp(error)){
            if(!error.empty()){
                std::strcpy(err, error.c_str());
            }else{
                std::strcpy(err, "Startup build Failed!");
            }
            return false;
        }
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

}