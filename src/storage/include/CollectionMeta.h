#pragma once
#include <string>

namespace zoro::storage{

class CollectionMeta {
public:
    explicit CollectionMeta(const std::string& collection_path);
    void InitDefault(int dimension, std::string distance, int coll_id, std::string collection_name);
    int GetDimensions() const;
    std::string GetDistance() const;
    int GetCollectionId() const;
    void SetDimensions(int dims);

private:
    std::string meta_path_;
};

}