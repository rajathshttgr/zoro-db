#include "storage/include/StorageEngine.h"
#include "api/cli/CollectionService.h"
#include "api/cli/CollectionService.h"
#include "api/cli/cli.h"

int main() {
    zoro::storage::StorageEngine storage("../../.data");
    zoro::core::CollectionManager manager(&storage);
    zoro::api::CollectionService service(&manager);
    zoro::cli::Cli cli(&service);

    cli.Run();
    return 0;
}
