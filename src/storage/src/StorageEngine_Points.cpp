#include "StorageEngine.h"
#include "CollectionMeta.h"
#include "FileUtils.h"
#include "struct.h"
#include <fstream>

namespace zoro::storage {

bool StorageEngine::UpsertPoints(
    const std::string& coll_name,
    int point_id,
    const std::vector<float>& vectors,
    const json& payload
) {
    std::string coll_path = collection_root_ + "/" + coll_name;
    CollectionMeta metaInfo(coll_path);

    // VECTOR
    uint64_t vec_offset = FileUtils::appendBinaryData(
        coll_path + "/vectors.bin",
        reinterpret_cast<const char*>(vectors.data()),
        vectors.size() * sizeof(float)
    );

    auto vec_result = FileUtils::updateIndexFile(
        coll_path + "/vectors.idx",
        point_id,
        vec_offset,
        vectors.size() * sizeof(float),
        0
    );

    // PAYLOAD 
    std::string payload_str = payload.dump();

    uint64_t payload_offset = FileUtils::appendBinaryData(
        coll_path + "/payload.bin",
        payload_str.data(),
        payload_str.size()
    );

    auto payload_result = FileUtils::updateIndexFile(
        coll_path + "/payload.idx",
        point_id,
        payload_offset,
        payload_str.size(),
        0
    );

    // CONSISTENCY
    if (vec_result != payload_result)
        return false;

    if (vec_result == IndexUpdateResult::Inserted) {
        metaInfo.IncrementPointsCount(1);
    }

    return true;
}


bool StorageEngine::DeletePoints(const std::string& coll_name, int point_id) {
    std::string coll_path = collection_root_ + "/" + coll_name;
    CollectionMeta metaInfo(coll_path);

    uint64_t offset = 0;
    uint32_t length = 0;
    uint8_t flag_delete = 1;

    auto vec_result = FileUtils::updateIndexFile(
        coll_path + "/vectors.idx",
        point_id,
        offset,
        length,
        flag_delete
    );

    auto payload_result = FileUtils::updateIndexFile(
        coll_path + "/payload.idx",
        point_id,
        offset,
        length,
        flag_delete
    );

    // inconsistent state = corruption
    if ((vec_result == IndexUpdateResult::Deleted &&
        payload_result != IndexUpdateResult::Deleted) ||
        (payload_result == IndexUpdateResult::Deleted &&
        vec_result != IndexUpdateResult::Deleted)) {
        return false;
    }

    if (vec_result == IndexUpdateResult::Deleted) {
        metaInfo.DecrementPointsCount(1);
    }

    // NoOp is success (idempotent delete)
    return true;
}


int StorageEngine::CountPoints(const std::string& coll_name) {
    if (!StorageEngine::CollectionExists(coll_name)) {
        return 0;
    }
    std::string coll_path = collection_root_ + "/" + coll_name;
    CollectionMeta metaInfo(coll_path);
    return metaInfo.GetPointsCount();
}


bool StorageEngine::LoadAllVectors(
    const std::string& coll_name,
    std::vector<float>& out_vectors,
    std::vector<uint64_t>& out_ids
) {
    out_vectors.clear();
    out_ids.clear();

    std::string coll_path = collection_root_ + "/" + coll_name;
    std::string vec_bin_path = coll_path + "/vectors.bin";
    std::string vec_idx_path = coll_path + "/vectors.idx";

    std::ifstream idx_file(vec_idx_path, std::ios::binary);
    if (!idx_file.is_open()) {
        return false;
    }

    while (true) {
        VectorIndexEntry entry;
        idx_file.read(reinterpret_cast<char*>(&entry), sizeof(entry));

        if (!idx_file) {
            break; // EOF
        }

        if (entry.is_deleted) {
            continue;
        }

        // Read raw vector bytes
        std::string raw =
            FileUtils::readBinaryData(
                vec_bin_path,
                entry.offset,
                entry.length
            );

        if (raw.size() != entry.length) {
            return false;
        }

        // Convert bytes -> floats
        size_t num_floats = entry.length / sizeof(float);
        const float* vec_ptr =
            reinterpret_cast<const float*>(raw.data());

        // Append
        out_vectors.insert(
            out_vectors.end(),
            vec_ptr,
            vec_ptr + num_floats
        );

        out_ids.push_back(entry.point_id);
    }

    return true;
}

}