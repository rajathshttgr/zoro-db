#pragma once

#include <memory>

namespace zoro {
namespace wal { class WALWriter; }
namespace storage { class StorageEngine; }
namespace core { class CollectionManager; }
namespace services { class CollectionService; }
}

// extern declarations
extern std::unique_ptr<zoro::wal::WALWriter> g_wal;
extern std::unique_ptr<zoro::storage::StorageEngine> g_storage;
extern std::unique_ptr<zoro::core::CollectionManager> g_manager;
extern std::unique_ptr<zoro::services::CollectionService> g_service;