#include "config.h"
#include "wal/include/wal_writer.h"
#include "storage/include/StorageEngine.h"
#include "services/include/CollectionService.h"
#include <iostream>

int main() {
    std::string dataPath = zoro::config::getDataPath();

    zoro::wal::WALWriter wal(dataPath);
    zoro::storage::StorageEngine storage(dataPath);
    zoro::core::CollectionManager manager(dataPath, &storage, wal);
    zoro::services::CollectionService service(&manager);

    return 0;
}