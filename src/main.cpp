#include "config.h"
#include "storage/include/StorageEngine.h"
#include "api/cli/CollectionService.h"
#include "api/cli/cli.h"

int main() {
    zoro::storage::StorageEngine storage(zoro::config::DEFAULT_DATA_PATH);
    zoro::core::CollectionManager manager(&storage);
    zoro::api::CollectionService service(&manager);
    zoro::cli::Cli cli(&service);

    cli.Run();
    return 0;
}
