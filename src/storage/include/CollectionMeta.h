#pragma once
#include <string>

namespace zoro::storage{

class CollectionMeta {
public:
    explicit CollectionMeta(const std::string& collection_path);
    void InitDefault(int dimension, std::string distance, int coll_id, std::string collection_name);
    int GetCollectionId() const;
    std::string GetDistance() const;
    void SetDimensions(int dims);
    int GetDimensions() const;

private:
    std::string meta_path_;
};

}