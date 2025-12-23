#include "config.h"
#include "wal/include/wal_writer.h"
#include "storage/include/StorageEngine.h"
#include "api/CollectionService.h"
#include "api/cli/cli.h"
#include <iostream>

int main() {
    std::string dataPath = zoro::config::getDataPath();

    zoro::wal::WALWriter wal(dataPath);
    zoro::storage::StorageEngine storage(dataPath, &wal);
    zoro::core::CollectionManager manager(&storage);
    zoro::api::CollectionService service(&manager);
    zoro::cli::Cli cli(&service);

    cli.Run();
    return 0;
}