#include "./CollectionService.h"

namespace zoro::services {

CollectionService::CollectionService(zoro::core::CollectionManager* manager)
    : manager_(manager), metadata_cache_(std::make_shared<MetadataCache>()) {}

}