#pragma once
#include <string>

namespace zoro::storage{

class CollectionMeta {
public:
    explicit CollectionMeta(const std::string& collection_path);
    void InitDefault(int dimension, std::string distance, std::string collection_name);
    void SetStatus(const std::string& status);
    int GetCollectionId() const;
    std::string GetDistance() const;
    void SetDimensions(int dims);
    int GetDimensions() const;
    void IncrementPointsCount(int count=1);
    void DecrementPointsCount(int count=1);
    int GetPointsCount() const;

private:
    std::string meta_path_;
};

}