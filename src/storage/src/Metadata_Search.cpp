#include "StorageEngine.h"
#include "FileUtils.h"

namespace zoro::storage {

std::optional<PointInfo> StorageEngine::GetMetadataByPointId(
    const std::string& collection_name,
    int point_id,
    std::string& err
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
        err = "Point ID not found";
        return std::nullopt;
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

std::vector<ScrollPointInfo> StorageEngine::ListPointMetadata(
    const std::string& collection_name,
    int limit,
    std::string& err
) {
    std::vector<ScrollPointInfo> results;

    std::string coll_path = collection_root_ + "/" + collection_name;

    std::vector<uint32_t> active_ids;
    bool res = FileUtils::ListActivePointIds(
        coll_path + "/payload.idx",
        active_ids,
        limit
    );

    if (!res) {
        err = "Failed to list active point IDs";
        return results;
    }

    for (uint32_t id : active_ids) {
        uint64_t offset;
        uint32_t length;

        bool found = FileUtils::findPayloadIndex(
            coll_path + "/payload.idx",
            id,
            offset,
            length
        );

        if (!found) {
            continue; // skip missing entries
        }

        std::string payload_str =
            FileUtils::readBinaryData(coll_path + "/payload.bin", offset, length);

        json payload = json::parse(payload_str);

        ScrollPointInfo info;
        info.point_id = id;
        info.payload = payload;

        results.push_back(info);
    }

    return results;
} 

}