#include "StorageEngine.h"
#include "FileUtils.h"

namespace zoro::storage {

std::optional<PointInfo> StorageEngine::GetMetadataByPointId(
    const std::string& collection_name,
    int point_id
) {
    std::string coll_path = collection_root_ + "/" + collection_name;

    uint64_t offset;
    uint32_t length;

    bool found = FileUtils::findPayloadIndex(
        coll_path + "/payload.idx",
        point_id,
        offset,
        length
    );

    if (!found) {
        throw std::runtime_error("Point ID not found");
    }

    std::string payload_str =
        FileUtils::readBinaryData(coll_path + "/payload.bin", offset, length);

    json payload = json::parse(payload_str);

    PointInfo info;
    info.status = "ok";
    info.point_id = point_id;
    info.payload = payload;

    return info;
}


} // namespace zoro::storage