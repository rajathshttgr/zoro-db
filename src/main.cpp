#include "config.h"
#include "storage/include/StorageEngine.h"
#include "api/cli/CollectionService.h"
#include "api/cli/cli.h"
#include <iostream>

int main() {
    std::string dataPath = zoro::config::getDataPath();

    zoro::storage::StorageEngine storage(dataPath);
    zoro::core::CollectionManager manager(&storage);
    zoro::api::CollectionService service(&manager);
    zoro::cli::Cli cli(&service);

    cli.Run();
    return 0;
}
